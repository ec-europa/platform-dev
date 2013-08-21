<?php

/**
 * @file
 * Add a link to the main menu.
 */

/**
* Implementation of hook_views_default_views_alter().
*/
function links_standard_views_default_views_alter(&$views) {
  if (array_key_exists('links', $views)) {
    $view=$views['links'];

    /* Display: Page */
    $handler = $view->display['page']->handler;
    $handler->display->display_options['path'] = 'links';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Links';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
  }
}
