<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\VariableContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

/**
 * Context for overriding Drupal variables.
 *
 * This context can be used by other contexts to modify Drupal variables. It
 * ensures their initial values are restored after each scenario.
 */
class VariableContext implements Context {

  /**
   * Initial variable values to restore at the end of the test.
   *
   * @var array
   */
  protected $initialVariables = array();

  /**
   * Sets the value of a Drupal variable.
   *
   * The initial value of the value is remembered for later restore.
   *
   * @param string $name
   *   Name of the variable.
   * @param mixed $value
   *   New value for the variable.
   *
   * @Given I request to change the variable :name to :value
   *
   * @When I change the variable :name to :value
   */
  public function setVariable($name, $value) {
    if (!array_key_exists($name, $this->initialVariables)) {
      $this->initialVariables[$name] = variable_get($name);
    }

    variable_set($name, $value);
  }

  /**
   * Deletes the value of a Drupal variable.
   *
   * The initial value of the value is remembered for later restore.
   *
   * @param string $name
   *   Name of the variable.
   */
  public function deleteVariable($name) {
    if (!array_key_exists($name, $this->initialVariables)) {
      $this->initialVariables[$name] = variable_get($name);
    }

    variable_del($name);
  }

  /**
   * Restores the initial values of the Drupal variables.
   *
   * @AfterScenario
   */
  public function restoreVariables() {
    foreach ($this->initialVariables as $variable => $value) {
      if ($value === NULL) {
        variable_del($variable);
      }
      else {
        variable_set($variable, $value);
      }
    }
    $this->initialVariables = array();
  }

}
