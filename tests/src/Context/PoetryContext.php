<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\PoetryContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Drupal\nexteuropa\Component\PyStringYamlParser;

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

}
