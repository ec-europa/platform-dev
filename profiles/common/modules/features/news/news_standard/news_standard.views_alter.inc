<?php

/**
 * @file
 * Alters the view for news feature.
 */

/**
 * Implements hook_views_default_views_alter().
 */
function news_standard_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('news', $views)) {
    $view = $views['news'];

    /* Display: News list page */
    $handler = $view->display['page']->handler;
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'News';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
  }
}
