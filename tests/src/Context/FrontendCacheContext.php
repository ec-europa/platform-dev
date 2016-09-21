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
    $this->variables->setVariable('fp_tag_for_cache_page', $arg1);

    $server = $this->getServer();

    // Do not let poor man's cron interfere with our test.
    $this->variables->setVariable('cron_safe_threshold', 0);

    $this->variables->setVariable('page_cache_invoke_hooks', TRUE);
    $this->variables->setVariable('cache', TRUE);
    $this->variables->setVariable('cache_lifetime', FALSE);
    $this->variables->setVariable('page_cache_without_database', FALSE);
    $cache_handler_file = drupal_get_path('module', 'flexible_purge') . '/flexible_purge.cache.inc';
    // $cache_backends = variable_get('cache_backends', array());
    // $cache_backends[] = $cache_handler_file;
    // $this->variables->setVariable('cache_backends', $cache_backends);
    // Workaround for cache handler class not getting loaded properly by the
    // 3 lines above.
    require_once 'includes/registry.inc';
    _registry_parse_files([$cache_handler_file => ['module' => 'flexible_purge', 'weight' => 0]]);
    $this->variables->setVariable('cache_class_cache_page', 'FlexiblePurgeCache');
    $this->variables->setVariable('fp_keep_caching_for_cache_page', 'DrupalDatabaseCache');
    $this->variables->setVariable('fp_http_targets_for_cache_page', array($server->getConnectionString()));

    // Act as if the flexible purge page cache just got cleared.
    $this->variables->setVariable('fp_latest_clear_for_cache_page', time());

    // Set minimum cache lifetime to something high enough so a full
    // cache clear does not get triggered during 1 scenario. Currently 10
    // minutes.
    $this->variables->setVariable('fp_min_cache_lifetime_for_cache_page', 60 * 10);

    // The builtin webserver of PHP which is used by our HTTP mock server, does
    // not support the PURGE method which flexible_purge uses by default.
    // Configure it to use POST instead.
    $this->variables->setVariable(
      'fp_http_request_for_cache_page', array(
        'method' => 'POST',
        'path' => '/invalidate',
        'headers' => array(
          'X-Invalidate-Tag' => '@{tag}',
          'X-Invalidate-Host' => '@{host}',
          'X-Invalidate-Base-Path' => '@{base_path}',
          'X-Invalidate-Type' => '@{clear_type}',
          'X-Invalidate-Regexp' => '@{path_regexp}',
        ),
      )
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
      $rule = entity_create(
        'nexteuropa_varnish_cache_purge_rule',
        array(
          'content_type' => $rule['Content Type'],
          'paths' => preg_replace('/\s*,\s*/', "\n", $rule['Paths to Purge']),
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

    assert($purge_request->getHeader('X-Invalidate-Tag')->toArray(), equals([$arg1]));
    assert($purge_request->getHeader('X-Invalidate-Type')->toArray(), equals(['regexp-multiple']));
    assert($purge_request->getHeader('X-Invalidate-Regexp')->toArray(), equals([$path_string]));
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

}
