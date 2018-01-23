<?php

/**
 * @file
 * Code for altering the view of the standard Survey feature.
 */

/**
 * Implements hook_views_default_views_alter().
 */
function survey_standard_views_default_views_alter(&$views) {
  if (array_key_exists('surveys_list', $views)) {
    $view = $views['surveys_list'];

    // Display: Page.
    $handler = $view->display['page_1']->handler;
    $handler->display->display_options['path'] = 'survey';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Surveys';
    $handler->display->display_options['menu']['weight'] = '15';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
  }
}
