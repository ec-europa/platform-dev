<?php

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
   * Parameters passed from the configuration.
   *
   * @var array
   */
  protected $params = [];

  /**
   * PoetryContext constructor.
   *
   * @param string $wsdl
   *   The wsdl to use in the tests.
   */
  public function __construct($wsdl)
  {
    $this->params = [
      'wsdl' => $wsdl,
    ];
  }

  /**
   * Get a parameter.
   *
   * @param string $item
   *   The parameter to get.
   *
   * @return mixed
   *   The value of the parameter.
   */
  private function getParam($item) {
    return array_key_exists($item, $this->params) ? $this->params[$item] : NULL;
  }

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
    $yaml = $parser->parse()
      ->replace(['{{ wsdl }}' => $this->getParam('wsdl')])
      ->getYaml();

    $this->variables->setVariable('poetry_service', $yaml);
  }

}
