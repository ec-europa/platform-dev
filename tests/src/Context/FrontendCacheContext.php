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
  public function __construct($mock_server_port = 8888) {
    $this->mockServerPort = $mock_server_port;
  }

  /**
   * Gets the mocked HTTP server.
   *
   * Initializes the server if it was not used before.
   * By default it responds to any POST requests to /invalidate with 200 OK,
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
        ->pathIs('/invalidate')
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
   * Configures the frontend cache integration for testing purposes.
   *
   * @Given :arg1 is configured as the purge application tag
   */
  public function valueIsConfiguredAsThePurgeApplicationTag($arg1) {
    $this->variables->setVariable('nexteuropa_varnish_tag', $arg1);

    $server = $this->getServer();

    // Do not let poor man's cron interfere with our test.
    $this->variables->setVariable('cron_safe_threshold', 0);

    // The builtin webserver of PHP which is used by our HTTP mock server, does
    // not support the PURGE method which flexible_purge uses by default.
    // Configure it to use POST instead.
    $this->variables->setVariable('nexteuropa_varnish_request_method', 'POST');

    $this->variables->setVariable('nexteuropa_varnish_http_targets',
      array('http://' . $server->getConnectionString())
    );
  }

  /**
   * Inserts cache purge rules via the entity API.
   *
   * @Given the following cache purge rules:
   */
  public function theFollowingCachePurgeRules(TableNode $table) {
    $rules = $table->getHash();

    foreach ($rules as $rule) {
      if (trim($rule['Paths to Purge']) == '') {
        $paths = '';
      }
      else {
        $paths = preg_replace('/\s*,\s*/', "\n", $rule['Paths to Purge']);
      }

      $rule = entity_create(
        'nexteuropa_varnish_cache_purge_rule',
        array(
          'content_type' => $rule['Content Type'],
          'paths' => $paths,
        )
      );

      entity_save('nexteuropa_varnish_cache_purge_rule', $rule);
    }
  }

  /**
   * Asserts the cache purge rules displayed in the overview.
   *
   * @Then I see an overview with the following cache purge rules:
   */
  public function assertOverviewOfCachePurgeRules(TableNode $table) {
    $expected_rules = $table->getHash();

    $overview = $this->getCachePurgeRulesOverview();

    $rows = $overview->findAll('css', 'tr');

    \bovigo\assert\assert($rows, isOfSize(count($expected_rules)));

    /** @var Element $row */
    foreach (array_values($rows) as $i => $row) {
      $expected_rule = $expected_rules[$i];

      $this->assertOverviewCachePurgeRule($row, $expected_rule);
    }
  }

  /**
   * Gets the cache purge rules overview.
   *
   * @return Element
   *   The table body.
   */
  protected function getCachePurgeRulesOverview() {
    return $this->mink->getSession()->getPage()->find('css', 'table#frontend-cache-purge-rules > tbody');
  }

  /**
   * Asserts a particular row from the cache purge rules overview.
   *
   * @param Element $row
   *   The table row.
   * @param array $expected_rule
   *   The expected values for the cache purge rule.
   */
  protected function assertOverviewCachePurgeRule(Element $row, array $expected_rule) {
    /** @var Element[] $cells */
    $cells = $row->findAll('css', 'td');

    assert($cells[0]->getText(), equals($expected_rule['Content Type']));
    assert($cells[1]->getText(), equals($expected_rule['Paths to Purge']));
  }

  /**
   * Clicks a link in a specific table row given the number of that row.
   *
   * @When I click :arg1 next to the :nth cache purge rule
   */
  public function iClickLinkNextToTheNthCachePurgeRule($arg1, $nth) {
    $overview = $this->getCachePurgeRulesOverview();

    $matched = preg_match('/^[0-9]+/', $nth, $matches);
    assert($matched, equals(1));
    // In human language we start to count from 1, but in code from 0.
    // So we need to substract by 1.
    $row_number = $matches[0] - 1;

    $rows = $overview->findAll('css', 'tr');
    assert($rows, \bovigo\assert\predicate\hasKey($row_number));
    $row = $rows[$row_number];

    $link = $row->findLink($arg1);
    $link->click();
  }

  /**
   * Asserts that the web front end cache received certain purge requests.
   *
   * @Then the web front end cache was instructed to purge the following paths for the application tag :arg1:
   */
  public function theWebFrontEndCacheWasInstructedToPurgeTheFollowingPathsForTheApplicationTag($arg1, TableNode $table) {
    $requests = $this->getRequests();
    assert($requests, isOfSize(1));

    $purge_request = $requests->last();

    $rows = $table->getHash();

    $paths = array_map(
      function ($row) {
        return preg_quote(ltrim($row['Path'], '/'));
      },
      $rows
    );

    $path_string = '^(' . implode('|', $paths) . ')$';

    // Some of environments returns different paths. To pass the test given
    // environment path is removed from the assertion process.
    $content_url = preg_quote(ltrim(url(), '/'));
    $purge_request_paths = str_replace($content_url, '', $purge_request->getHeader('X-Invalidate-Regexp')->toArray());

    assert($purge_request->getHeader('X-Invalidate-Tag')->toArray(), equals([$arg1]));
    assert($purge_request->getHeader('X-Invalidate-Type')->toArray(), equals(['regexp-multiple']));
    assert($purge_request_paths, equals([$path_string]));
  }

  /**
   * Asserts that the web front end cache did not receive any purge requests.
   *
   * @Then the web front end cache was not instructed to purge any paths
   */
  public function theWebFrontEndCacheWasNotInstructedToPurgeAnyPaths() {
    $requests = $this->getRequests();
    assert($requests, isOfSize(0));
  }

  /**
   * Clean all requests created by rules on the server.
   *
   * @Then Execute all purge rules
   */
  public function executeAllRulePurge() {
    $requests = $this->getRequests();

    while ($requests->count() > 0) {
      $requests->pop();
    }
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

  /**
   * Removes all cache purge rules.
   *
   * @AfterScenario
   */
  public function purgeAllCacheRules() {
    if (module_exists('nexteuropa_varnish')) {
      $rules = entity_load('nexteuropa_varnish_cache_purge_rule');
      $rule_ids = array_keys($rules);
      entity_delete_multiple('nexteuropa_varnish_cache_purge_rule', $rule_ids);
    }
  }

  /**
   * Assert that a purge request was received.
   *
   * @Then the web front end cache was instructed to purge certain paths for the application tag :arg1
   */
  public function theWebFrontEndCacheWasInstructedToPurgeCertainPaths($arg1) {
    $requests = $this->getRequests();
    assert($requests, isOfSize(1));

    $purge_request = $requests->last();

    assert($purge_request->getHeader('X-Invalidate-Tag')->toArray(), equals([$arg1]));
    assert($purge_request->getHeader('X-Invalidate-Type')->toArray(), equals(['regexp-multiple']));
  }

  /**
   * Assert that the last purge request matches specific paths.
   *
   * @Then the web front end cache will not use existing caches for the following paths:
   */
  public function theWebFrontEndCacheWillNotUseExistingCachesForTheFollowingPaths(TableNode $table) {
    $purge_pattern = $this->getPurgePatternFromLastRequest();

    $paths = $this->getPathsFromTable($table);

    foreach ($paths as $path) {
      assert($path, matches('@' . $purge_pattern . '@'));
    }
  }

  /**
   * Assert that the last purge request does not match specific paths.
   *
   * @Then the web front end cache will still use existing caches for the following paths:
   */
  public function theWebFrontEndCacheWillStillUseExistingCachesForTheFollowingPaths(TableNode $table) {
    $purge_pattern = $this->getPurgePatternFromLastRequest();

    $paths = $this->getPathsFromTable($table);

    foreach ($paths as $path) {
      assert($path, not(matches('@' . $purge_pattern . '@')));
    }
  }

  /**
   * Retrieve the purge pattern from the last purge request.
   *
   * @return string
   *   The purge pattern, which is a regular expression.
   */
  private function getPurgePatternFromLastRequest() {
    $requests = $this->getRequests();
    assert($requests, isOfSize(1));

    $purge_request = $requests->last();

    $purge_patterns = $purge_request
      ->getHeader('X-Invalidate-Regexp')
      ->toArray();

    $purge_pattern = reset($purge_patterns);

    return $purge_pattern;
  }

  /**
   * Retrieve the values in the 'Path' column.
   *
   * @param TableNode $table
   *   The Behat Gherkin table node.
   *
   * @return string[]
   *   The values in the 'Path' column, with any leading slash removed.
   */
  private function getPathsFromTable(TableNode $table) {
    $rows = $table->getHash();
    $paths = array_map(
      function ($row) {
        return ltrim($row['Path'], '/');
      },
      $rows
    );
    return $paths;
  }

  /**
   * Configures basic authentication.
   *
   * @When nexteuropa_varnish is configured to authenticate with user :arg1 and password :arg2
   */
  public function nexteuropaVarnishIsConfiguredToAuthenticateWithUserAndPassword($arg1, $arg2) {
    $this->variables->setVariable('nexteuropa_varnish_request_user', $arg1);
    $this->variables->setVariable('nexteuropa_varnish_request_password', $arg2);
  }

  /**
   * Assert that the last request was authenticated.
   *
   * @Then the web front end cache received a request authenticated with user :arg1 and password :arg2
   */
  public function theWebFrontEndCacheReceivedRequestAuthenticatedWithUserAndPassword($arg1, $arg2) {
    $requests = $this->getRequests();
    $purge_request = $requests->last();

    $authorization = $purge_request->getHeader('Authorization')->toArray();
    $authorization = reset($authorization);

    assert($authorization, matches('@Basic [ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=]+@'));

    $base64_user_password = substr($authorization, 5);
    $decoded_user_password = base64_decode($base64_user_password);

    assert($decoded_user_password, equals("{$arg1}:{$arg2}"));
  }

  /**
   * Set up the mock front end cache to refuse the HTTP authentication.
   *
   * The mock will return a 401 Unauthorized response.
   *
   * @When the web front end cache will refuse the authentication credentials
   */
  public function theWebFrontEndCacheWillRefuseTheAuthenticationCredentials() {
    $server = $this->getServer();

    $mock = new MockBuilder(new MatcherFactory(), new ExtractorFactory());
    $mock
      ->when()
      ->methodIs('POST')
      ->pathIs('/invalidate')
      ->then()
      ->statusCode(401);

    $server->setUp($mock->flushExpectations());
  }

}
