<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\RulesContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\PyStringNode;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Class RulesContext.
 *
 * @package Drupal\nexteuropa\Context
 */
class RulesContext extends RawDrupalContext {

  /**
   * Rules created during test execution.
   *
   * @var array
   */
  private $rules = [];

  /**
   * Import rule.
   *
   * @Given I have the following rule:
   */
  public function importRule(PyStringNode $string) {
    $raw = $string->getRaw();
    $decoded = json_decode($raw, TRUE);
    $error = '';
    $rule = rules_import(json_encode($decoded), $error);
    if ($rule === FALSE) {
      throw new \Exception($error);
    }
    $rule->save();
    $this->rules[] = $rule->name;
  }

  /**
   * Remove rules created during test execution.
   *
   * @AfterScenario
   */
  public function removeRules() {
    foreach ($this->rules as $name) {
      $rule = rules_config_load($name);
      $rule->delete();
    }
    $this->rules = array();
  }

}
