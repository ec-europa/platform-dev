<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FrontendCacheContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\Element;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;
use function bovigo\assert\predicate\isOfSize;
use function bovigo\assert\predicate\matches;
use function bovigo\assert\predicate\not;
use InterNations\Component\HttpMock\Matcher\ExtractorFactory;
use InterNations\Component\HttpMock\Matcher\MatcherFactory;
use InterNations\Component\HttpMock\MockBuilder;
use InterNations\Component\HttpMock\RequestCollectionFacade;
use InterNations\Component\HttpMock\Server;

/**
 * Context for steps and assertions related to web frontend caching (Varnish).
 */
class FrontendCacheContext implements Context {

  /**
   * The Mink context.
   *
   * @var MinkContext
   */
  protected $mink;

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
   * @var Server
   */
  protected $server;

  /**
   * Facade to access requests made to the mocked HTTP server.
   *
   * @var RequestCollectionFacade
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
   * By default it responds to any POST requests to /solr with 200 OK,
   * additional behavior can be added in further steps.
   *
   * @return Server
   *   The mocked HTTP server.
   */
  protected function getServer() {
    if (!$this->server) {
      $this->server = new Server($this->mockServerPort, 'localhost');

      $this->server->start();

      // Accept any POSTS.
      $mock = new MockBuilder(new MatcherFactory(), new ExtractorFactory());
      $mock
        ->when()
        ->pathIs('/solr')
        ->methodIs('POST')
        ->then()
        ->statusCode(200);

      $this->server->setUp($mock->flushExpectations());
    }

    return $this->server;
  }

  /**
   * Gets the requests made to the mocked Integration backend.
   *
   * @return RequestCollectionFacade
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

    $this->mink = $environment->getContext(MinkContext::class);
    $this->variables = $environment->getContext(VariableContext::class);
  }

  /**
   * Configures the ApacheSolr integration for testing purposes.
   *
   * @Given the apachesolr integration is configured
   */
  public function apacheSolrIntegrationIsConfigured() {

  }

  /**
   * Asserts that the web front end cache received certain purge requests.
   *
   * @Then the apachesolr server was instructed to index a :arg1: node with title :arg2:
   */
  public function theApacheSolrServerWasInstructedToIndexANodeWithTitle($arg1, $arg2) {
    $requests = $this->getRequests();
    assert($requests, isOfSize(1));

    $index_request = $requests->last();
    // TODO: Assert index
  }

  /**
   * Asserts that the web front end cache did not receive any purge requests.
   *
   * @Then the apachesolr server was not instructed to index any node
   */
  public function theApacheSolrServerWasNotInstructedToIndexAnyNode() {
    $requests = $this->getRequests();
    assert($requests, isOfSize(0));
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
