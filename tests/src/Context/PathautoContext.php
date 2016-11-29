<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\PathautoContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Context for configuring the PathautoContext.
 */
class PathautoContext implements Context {

  /**
   * The variable context.
   *
   * @var VariableContext
   */
  protected $variableContext;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    $this->variableContext = $environment->getContext(VariableContext::class);
  }

  /**
   * Set a pathauto pattern value.
   *
   * @param string $name
   *    Pathauto pattern machine_name.
   * @param string $value
   *    Pathauto pattern value.
   *
   * @Given the pathauto :name pattern is set to :value
   *
   */
  public function setAliasPattern($name, $value) {
    $this->variableContext->setVariable($name, $value);
  }

}
