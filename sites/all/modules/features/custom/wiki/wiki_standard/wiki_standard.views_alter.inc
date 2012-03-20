<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function wiki_standard_views_default_views_alter(&$views) {
  if (array_key_exists('wiki_list', $views)) {
	$view=$views['wiki_list'];
	 
    /* Display: Page */
    $handler = $view->display['page_1']->handler;
    $handler->display->display_options['defaults']['empty'] = FALSE;
    $handler->display->display_options['path'] = 'wiki';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Wikis';
    $handler->display->display_options['menu']['weight'] = '15';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;

  }
}

