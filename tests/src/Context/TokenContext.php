<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Context for operations with tokens.
 */
class TokenContext implements Context {

  /**
   * The variable for DrupalContext.
   *
   * @var \Drupal\nexteuropa\Context\DrupalContext
   */
  private $drupalContext;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    // This allows to use the object DrupalContext on this context.
    $this->drupalContext = $environment->getContext('Drupal\nexteuropa\Context\DrupalContext');
  }

  /**
   * Replace the token value.
   *
   * @param string $text
   *   The text to check for replacement.
   *
   * @return string
   *   The text after token replacement.
   */
  public function replaceToken($text) {
    // last-created-node-id: Replace for the nid of the last created node.
    if (strpos($text, 'last-created-node-id')) {
      $text = $this->replaceByLastNid($text);
    }
    return $text;
  }

  /**
   * Replace the token value with the id of the last created node.
   *
   * @param string $text
   *   The text to check for replacement.
   *
   * @return string
   *   The text after token replacement.
   */
  public function replaceByLastNid($text) {
    return str_replace('last-created-node-id', $this->drupalContext->getLastNode(), $text);
  }

}
