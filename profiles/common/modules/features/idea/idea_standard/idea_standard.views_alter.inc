<?php
/**
 * Implements hook_views_default_views_alter().
 */
function idea_standard_views_default_views_alter(&$views) {
  if (array_key_exists('idea_list', $views)) {
    $view=$views['idea_list'];

    /* Display: Page */
    $handler = $view->display['page_1']->handler;
    $handler->display->display_options['defaults']['empty'] = FALSE;
    $handler->display->display_options['path'] = 'ideas';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Ideas';
    $handler->display->display_options['menu']['weight'] = '15';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    
    $handler->display->display_options['defaults']['empty'] = FALSE;
    /* No results behavior: Global: Text area */
    $handler->display->display_options['empty']['area']['id'] = 'area';
    $handler->display->display_options['empty']['area']['table'] = 'views';
    $handler->display->display_options['empty']['area']['field'] = 'area';
    $handler->display->display_options['empty']['area']['empty'] = TRUE;
    $handler->display->display_options['empty']['area']['content'] = 'No content found.';
    $handler->display->display_options['empty']['area']['format'] = 'full_html';
  }
}
