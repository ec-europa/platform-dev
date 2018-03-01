<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\PoetryContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Drupal\nexteuropa\Component\PyStringYamlParser;
use Drupal\ne_dgt_rules\DgtRulesTools;
use function bovigo\assert\assert;
use function bovigo\assert\predicate\equals;

/**
 * Class PoetryContext.
 *
 * @package Drupal\nexteuropa\Context
 */
class PoetryContext implements Context {
    /**
     * The variable context.
     *
     * @var VariableContext
     */
    protected $variables;

    /**
     * Gathers other contexts we rely on, before the scenario starts.
     *
     * @BeforeScenario @poetry
     */
    public function gatherContexts(BeforeScenarioScope $scope) {
        $environment = $scope->getEnvironment();
        $this->variables = $environment->getContext(VariableContext::class);
    }

    /**
     * Override Poetry settings.
     *
     * Important: remove poetry_service overrides from your settings.php as it
     * would override the following step.
     *
     * @param \Behat\Gherkin\Node\PyStringNode $string
     *   Settings in PyString format.
     *
     * @Given the following Poetry settings:
     */
    public function theFollowingPoetrySettings(PyStringNode $string) {
        $parser = new PyStringYamlParser($string);
        $this->variables->setVariable('poetry_service', $parser->parse());
    }

    /**
     * Asserts the cache purge rules displayed in the overview.
     *
     * @param \Behat\Gherkin\Node\TableNode $table
     *   Expected values of the identifier.
     *
     * @Then the following entity mapping entry has been created:
     */
    public function checkIfEntityMappingHasBeenCreated(TableNode $table) {
        // Getting expected data from the table and loading the mapping.
        $expected_values = $table->getRowsHash();
        $node = node_load($expected_values['entity_id']);
        $entity_mappings = DgtRulesTools::findMappingsByNode($node);

        // Asserting the mapping values.
        assert($expected_values['client_action'], equals($entity_mappings->client_action));
        assert($expected_values['entity_id'], equals($entity_mappings->entity_id));
        assert($expected_values['entity_type'], equals($entity_mappings->entity_type));
        assert($expected_values['code'], equals($entity_mappings->code));
        assert($expected_values['number'], equals($entity_mappings->number));
        assert($expected_values['part'], equals($entity_mappings->part));
        assert($expected_values['version'], equals($entity_mappings->version));
        assert($expected_values['year'], equals($entity_mappings->year));
    }

}
