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

/**
 * Context for steps and assertions related to web frontend caching (Varnish).
 */
class PiwikRulesContext implements Context {

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
   * Configures the nexteuropa PIWIK module to use advanced PIWIK rules.
   *
   * @Given the nexteuropa_piwik module is configured to use advanced PIWIK rules
   */
  public function nexteuropaPiwikIsConfiguredToUseAdvancedPiwikRules() {
    $this->variables->setVariable('nexteuropa_piwik_rules_state', TRUE);
    entity_info_cache_clear();
    menu_rebuild();
  }

  /**
   * Inserts cache purge rules via the entity API.
   *
   * @Given the following PIWIK rules:
   */
  public function theFollowingPiwikRules(TableNode $table) {
    $rules = $table->getHash();

    foreach ($rules as $rule) {
      $rule = entity_create(
        'nexteuropa_piwik_rule',
        array(
          'rule_language' => $rule['Rule language'],
          'rule_path' => $rule['Rule path'],
          'rule_path_type' => $rule['Rule path type'],
          'rule_section' => $rule['Rule section'],
        )
      );

      entity_save('nexteuropa_piwik_rule', $rule);
    }
  }

  /**
   * Asserts the PIWIK rules displayed in the overview.
   *
   * @Then I see an overview with the following PIWIK rules:
   */
  public function assertOverviewOfPiwikRules(TableNode $table) {
    $expected_rules = $table->getHash();

    $overview = $this->getPiwikRulesOverview();

    $rows = $overview->findAll('css', 'tr');

    \bovigo\assert\assert($rows, isOfSize(count($expected_rules)));

    /** @var Element $row */
    foreach (array_values($rows) as $i => $row) {
      $expected_rule = $expected_rules[$i];

      $this->assertOverviewPiwikRule($row, $expected_rule);
    }
  }

  /**
   * Gets the PIWIK rules overview.
   *
   * @return Element
   *   The table body.
   */
  protected function getPiwikRulesOverview() {
    return $this->mink->getSession()
      ->getPage()
      ->find('css', 'table#next-europa-piwik-rules > tbody');
  }

  /**
   * Asserts a particular row from the PIWIK rules overview.
   *
   * @param Element $row
   *   The table row.
   * @param array $expected_rule
   *   The expected values for the PIWIK rule.
   */
  protected function assertOverviewPiwikRule(Element $row, array $expected_rule) {
    /** @var Element[] $cells */
    $cells = $row->findAll('css', 'td');
    assert($cells[1]->getText(), equals($expected_rule['Rule section']));
    assert($cells[2]->getText(), equals($expected_rule['Rule language']));
    assert($cells[3]->getText(), equals($expected_rule['Rule path']));
    assert($cells[4]->getText(), equals($expected_rule['Rule path type']));
  }

  /**
   * Clicks a link in a specific table row given the number of that row.
   *
   * @When I click :arg1 next to the :nth PIWIK rule
   */
  public function iClickLinkNextToTheNthPiwikRule($arg1, $nth) {
    $overview = $this->getPiwikRulesOverview();

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
   * Removes all advanced PIWIK rules.
   *
   * @AfterScenario
   */
  public function purgeAllCacheRules() {
    if (module_exists('nexteuropa_piwik') && variable_get('nexteuropa_piwik_rules_state', FALSE)) {
      $rules = entity_load('nexteuropa_piwik_rule');
      $rule_ids = array_keys($rules);
      entity_delete_multiple('nexteuropa_piwik_rule', $rule_ids);
    }
  }

}
