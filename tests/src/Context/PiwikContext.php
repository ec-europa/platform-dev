<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\MinkExtension\Context\RawMinkContext;

/**
 * Context for steps and assertions related to the PIWIK configuration.
 */
class PiwikContext extends RawMinkContext {

  /**
   * The variable context.
   *
   * @var \VariableContext
   */
  protected $variables;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    $this->variables = $environment->getContext(VariableContext::class);
  }

  /**
   * The Piwik should be configurable with at least sideId and Paths.
   *
   * @Given The piwik is well configured with id :id and paths :piwik_paths
   */
  public function thePiwikIsWellConfiguredWithIdAndPaths($id, $piwik_paths) {
    $this->variables->setVariable('nexteuropa_piwik_site_id', $id);
    $this->variables->setVariable('nexteuropa_piwik_site_path', $piwik_paths);
  }

}
