<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;

class VariablesContext implements Context {

  /**
   * @var array
   */
  protected $variables;

  /**
   * @param array $values
   */
  public function __construct($values) {
    $this->variables = $values;
  }

  /**
   * @param string $name
   * @return mixed
   */
  public function getVariable($name) {
    return $this->variables[$name];
  }
}
