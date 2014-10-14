<?php

/**
 * @file
 * Alters the view for news feature.
 */

/**
* Implementation of hook_views_default_views_alter().
*/
function multisite_activity_standard_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('multisite_activity', $views)) {
    $view = $views['multisite_activity'];

    /* Display: Defaults */
    $handler = $view->display['default']->handler;
    $handler->display->display_options['title'] = 'Recent activity';

    /* Display: News list page */
    $handler = $view->display['page_1']->handler;
    $handler->display->display_options['path'] = 'activity';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Activity';
    $handler->display->display_options['menu']['weight'] = '70';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    
  }
}

