<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\FrontendCacheContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Behat\Tester\Exception\PendingException;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\Element;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;
use function bovigo\assert\predicate\isOfSize;

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

    // @todo Further configuration, mock the expected HTTP interface.
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
    throw new PendingException();
  }

  /**
   * Asserts that the web front end cache did not receive any purge requests.
   *
   * @Then the web front end cache was not instructed to purge any paths
   */
  public function theWebFrontEndCacheWasNotInstructedToPurgeAnyPaths() {
    throw new PendingException();
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
