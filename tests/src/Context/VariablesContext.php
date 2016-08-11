<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\VariablesContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

/**
 * Context for injecting arbitrary variables from the Behat configuration.
 *
 * Use this context in other contexts to retrieve secret or
 * environment-dependant values, like API keys, URLs, etc.
 */
class VariablesContext implements Context {

  /**
   * The variables.
   *
   * @var array
   */
  protected $variables;

  /**
   * Constructs a new VariablesContext.
   *
   * @param array $values
   *   The values.
   */
  public function __construct($values) {
    $this->variables = $values;
  }

  /**
   * Retrieves a specific variable.
   *
   * @param string $name
   *   Name of the variable.
   *
   * @return mixed
   *   The value of the variable.
   */
  public function getVariable($name) {
    return $this->variables[$name];
  }

}
