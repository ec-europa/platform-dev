<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\SliderContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Exception;

/**
 * Context with Media module related functionality.
 */
class SliderContext implements Context {

  /**
   * The Mink context.
   *
   * @var MinkContext
   */
  protected $mink;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->mink = $environment->getContext(MinkContext::class);
  }

  /**
   * Clone view.
   *
   * @Then I clone view :arg1 as :arg2
   */
  public function iCloneViewAs($arg1, $arg2) {
    // Load the view_machine_name view.
    $view = views_get_view($arg1);
    if (empty($arg1)) {
      throw new \Exception(sprintf('No view with id (%s)', $arg1));
    }
    // Clone the view.
    $view->clone_view();
    $view->name = $arg2;
    $view->save();
  }

  /**
   * Add view to context.
   *
   * @Then I add :arg1 view to :arg2 context section :arg3
   */
  public function iAddViewToContextSection($arg1, $arg2, $arg3) {
    views_get_all_views(TRUE);
    views_block_info();
    $block_ids = variable_get('views_block_hashes', array());
    $block_id = array_search($arg1, $block_ids);
    if (empty($block_id)) {
      throw new \Exception(sprintf('No view with id (%s)', $arg1));
    }
    multisite_drupal_toolbox_add_block_context($arg2, $block_id, 'views', $block_id, $arg3, 0);
  }

}
