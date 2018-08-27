<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Context for steps and assertions related to nexteuropa_laco module.
 */
class LacoContext implements Context {

  /**
   * The Smartloader Protocol-Relative URL.
   *
   * @var string
   */
  protected $smartloadurl;

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
   * Configures the LACO icon feature of the nexteuropa_laco module.
   *
   * @Given the LACO icon feature has been configured correctly
   */
  public function aValidLacoHasBeenConfigured() {
    $this->variableContext->setVariable('nexteuropa_laco_enable_laco_icon_feature', 1);
    $this->variableContext->setVariable('nexteuropa_laco_smartloader_prurl', 'http://europa.eu/webtools/load.js');
    /*$this->variableContext->setVariable('nexteuropa_laco_icon_include', array(
      '#block-system-main',
      '#sidebar-left',
      '#sidebar-right',
      '.page-content aside',
    ));
    $this->variableContext->setVariable('nexteuropa_laco_icon_exclude', array());
    $this->variableContext->setVariable('nexteuropa_laco_icon_document_coverage', 'any');
    $this->variableContext->setVariable('nexteuropa_laco_icon_page_coverage', 'any');
    $this->variableContext->setVariable('nexteuropa_laco_icon_language_coverage', 'eu');
    $this->variableContext->setVariable('nexteuropa_laco_icon_type', 'dot');
    $this->variableContext->setVariable('nexteuropa_laco_visibility_pages', 0);
    $this->variableContext->setVariable('nexteuropa_laco_excluded_paths', "admin\nadmin/ *\nbatch\nnode/add*\nnode/ * / * \nuser/ * / *");*/
  }

}