<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FrontendCacheContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;
use function bovigo\assert\predicate\isNotEqualTo;
use function bovigo\assert\predicate\hasKey;
use InterNations\Component\HttpMock\Matcher\ExtractorFactory;
use InterNations\Component\HttpMock\Matcher\MatcherFactory;
use InterNations\Component\HttpMock\MockBuilder;
use InterNations\Component\HttpMock\RequestCollectionFacade;
use InterNations\Component\HttpMock\Server;

/**
 * Context for steps and assertions related to ApacheSolr.
 */
class ApacheSolrContext implements Context {

  /**
   * The variable context.
   *
   * @var VariableContext
   */
  protected $variables;

  /**
   * The port the mocked HTTP server should listen on.
   *
   * @var int
   */
  protected $mockServerPort;

  /**
   * The mocked HTTP server.
   *
   * @var InterNations\Component\HttpMock\Server
   */
  protected $server;

  /**
   * Facade to access requests made to the mocked HTTP server.
   *
   * @var InterNations\Component\HttpMock\RequestCollectionFacade
   */
  protected $requests;

  /**
   * FrontendCacheContext constructor.
   *
   * @param int $mock_server_port
   *   The port the mocked HTTP server should listen on.
   */
  public function __construct($mock_server_port = 8983) {
    $this->mockServerPort = $mock_server_port;
  }

  /**
   * Gets the mocked HTTP server.
   *
   * Initializes the server if it was not used before.
   *
   * @return InterNations\Component\HttpMock\Server
   *   The mocked HTTP server.
   */
  protected function getServer() {
    if (!$this->server) {
      $this->server = new Server($this->mockServerPort, 'localhost');

      $this->server->start();

      // Accept any POSTS.
      $mock = new MockBuilder(new MatcherFactory(), new ExtractorFactory());
      $mock
        ->once()
        ->when()
        ->pathIs('/solr/update?wt=json')
        ->methodIs('POST')
        ->then()
        ->statusCode(100);
      $mock
        ->when()
        ->pathIs('/solr/update?wt=json')
        ->methodIs('POST')
        ->then()
        ->statusCode(200);
      $mock
        ->when()
        ->pathIs('/solr/admin/ping')
        ->methodIs('HEAD')
        ->then()
        ->statusCode(200);
      $mock
        ->when()
        ->pathIs('/solr/admin/system')
        ->methodIs('GET')
        ->then()
        ->statusCode(200);

      $this->server->setUp($mock->flushExpectations());
    }
    return $this->server;
  }

  /**
   * Gets the requests made to the mocked Integration backend.
   *
   * @return InterNations\Component\HttpMock\RequestCollectionFacade
   *   The requests facade.
   */
  protected function getRequests() {
    if (!$this->requests) {
      $this->requests = new RequestCollectionFacade($this->server->getClient());
    }

    return $this->requests;
  }

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->variables = $environment->getContext(VariableContext::class);
  }

  /**
   * Configures the ApacheSolr integration for testing purposes.
   *
   * @Given the apachesolr integration is configured
   */
  public function apacheSolrIntegrationIsConfigured() {
    $this->getServer();

    // Do not let poor man's cron interfere with our test.
    $this->variables->setVariable('cron_safe_threshold', 0);
  }

  /**
   * Index any remaining nodes in the site.
   *
   * @Given there are no nodes to index in apachesolr
   */
  public function thereAreNoNodesToIndexInApachesolr() {
    module_load_include('inc', 'apachesolr', 'apachesolr.index');
    apachesolr_index_entities('solr', 50);
    $requests = $this->getRequests();
    while ($requests->count() > 0) {
      $requests->pop();
    }
  }

  /**
   * Asserts that apachesolr received a request to index a node.
   *
   * @Then the apachesolr server was instructed to index a :arg1 node with title :arg2
   */
  public function theApacheSolrServerWasInstructedToIndexNodeWithTitle($arg1, $arg2) {

    $requests = $this->getRequests();
    $index_request = $requests->last();
    $solr_request = (string) $index_request->getBody();

    // Assert the last request is a POST.
    assert($index_request->getMethod(), equals('POST'));

    // Assert there is only one document in the request.
    assert(substr_count($solr_request, '<doc>'), equals(1));

    // Get the node title from the request.
    preg_match('~<field name="label">([^>]*)<\/field>~', $solr_request, $match);
    assert(count($match), equals(2));
    $node_title = $match[1];
    assert($node_title, equals($arg2));
    // Get the node type from the request.
    preg_match('~<field name="bundle">([^>]*)<\/field>~', $solr_request, $match);
    assert(count($match), equals(2));
    $node_type = $match[1];
    assert($node_type, equals($arg1));
  }

  /**
   * Asserts that apachesolr did not receive any index requests.
   *
   * @Then the apachesolr server was not instructed to index any node
   */
  public function theApacheSolrServerWasNotInstructedToIndexAnyNode() {
    $requests = $this->getRequests();
    $index_request = $requests->last();
    assert($index_request->getMethod(), isNotEqualTo('POST'));
  }

  /**
   * Asserts that apachesolr received a request to remove a node from the index.
   *
   * @Then the apachesolr server was instructed to remove a node from the index
   */
  public function theApacheSolrServerWasInstructedToRemoveNodeFromIndex() {
    $requests = $this->getRequests();
    $index_request = $requests->last();
    // Assert the last request is a POST.
    assert($index_request->getMethod(), equals('POST'));

    $solr_request = (string) $index_request->getBody();
    // Assert the request is for deleting a node.
    assert(substr_count($solr_request, '<delete>'), equals(1));
  }

  /**
   * Asserts that a facet is enabled for a searcher.
   *
   * @Then the facet :arg1 should be enabled for the searcher :arg2
   */
  public function theFacetShouldBeEnabledForTheSearcher($arg1, $arg2) {
    $enabled_facets = facetapi_get_enabled_facets($arg2);
    assert($enabled_facets, hasKey($arg1));
  }

  /**
   * Stops the mock HTTP server if it was started.
   *
   * @AfterScenario
   */
  public function stopMockServer() {
    if ($this->server && $this->server->isStarted()) {
      $this->server->stop();
    }
  }

}
