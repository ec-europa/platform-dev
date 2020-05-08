<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
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
  public function __construct($wsdl) {
    $this->params = [
      'wsdl' => $wsdl,
    ];
  }

  /**
   * Get the token replacements.
   *
   * @return array
   *   A keyed array of the token and token value.
   */
  public function getReplacements() {
    $replacements = [];

    foreach ($this->params as $key => $value) {
      $key = '{{ ' . $key . ' }}';
      $replacements[$key] = $value;
    }

    return $replacements;
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
      ->replace($this->getReplacements())
      ->getYaml();

    $this->variables->setVariable('poetry_service', $yaml);
  }

  /**
   * Set variable with replacements.
   *
   * @param string $name
   *   Name of the variable.
   * @param mixed $value
   *   New value for the variable.
   *
   * @Given I change the poetry variable :name to :value
   */
  public function iChangeThePoetryVariable($name, $value) {
    $replacements = $this->getReplacements();
    $value = str_replace(array_keys($replacements), array_values($replacements), $value);

    variable_set($name, $value);
  }

}
