<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function news_standard_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('news', $views)) {
    $view=$views['news'];
	
    /* Display: News list page */
    $handler = $view->new_display('page', 'News list page', 'page');
    $handler->display->display_options['path'] = 'news';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'News';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;	 
  }
}

