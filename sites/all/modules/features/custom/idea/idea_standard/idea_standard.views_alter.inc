<?php

/**
* Implementation of hook_views_default_views_alter().
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
	
  }
}

