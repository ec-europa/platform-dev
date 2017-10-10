<?php

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Class ViewsContext.
 *
 * @package Drupal\nexteuropa\Context
 */
class ViewsContext extends RawDrupalContext {

  /**
   * Views created during test execution.
   *
   * @var \view[]
   */
  protected $views = [];

  /**
   * Import given view.
   *
   * @Given a content view with machine name :machine_name is available
   */
  public function createView($machine_name) {
    $view = $this->getContentView($machine_name);
    $view->save();
    $this->views[] = $view;
  }

  /**
   * Delete views imported during test execution.
   *
   * @AfterScenario
   */
  public function deleteViews() {
    foreach ($this->views as $view) {
      views_delete_view($view);
    }
  }

  /**
   * Provide a test content view.
   *
   * @param string $machine_name
   *    View machine name.
   *
   * @return \view
   *    View object, not yet saved.
   */
  protected function getContentView($machine_name) {
    $view = new \view();
    $view->name = $machine_name;
    $view->vid = 'new';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'node';
    $view->human_name = $machine_name;
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'full';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    return $view;
  }

}
