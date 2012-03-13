<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function events_standard_views_default_views_alter(&$views) {
  if (array_key_exists('calendar', $views)) {
	$view=$views['calendar'];
	 
    /* Display: Month */
    $handler = $view->new_display('page', 'Month', 'month');
    $handler->display->display_options['path'] = 'calendar/month';
    $handler->display->display_options['menu']['type'] = 'default tab';
    $handler->display->display_options['menu']['title'] = 'Month';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['tab_options']['type'] = 'normal';
    $handler->display->display_options['tab_options']['title'] = 'Events';
    $handler->display->display_options['tab_options']['weight'] = '2';
    $handler->display->display_options['tab_options']['name'] = 'main-menu';

    /* Display: Week */
    $handler = $view->new_display('page', 'Week', 'week');
    $handler->display->display_options['path'] = 'calendar/week';
    $handler->display->display_options['menu']['type'] = 'tab';
    $handler->display->display_options['menu']['title'] = 'Week';
    $handler->display->display_options['menu']['weight'] = '2';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;

    /* Display: Day */
    $handler = $view->new_display('page', 'Day', 'day');	
    $handler->display->display_options['path'] = 'calendar/day';
    $handler->display->display_options['menu']['type'] = 'tab';
    $handler->display->display_options['menu']['title'] = 'Day';
    $handler->display->display_options['menu']['weight'] = '3';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;	
	
    /* Display: Year */
    $handler = $view->new_display('page', 'Year', 'year');	
    $handler->display->display_options['path'] = 'calendar/year';
    $handler->display->display_options['menu']['type'] = 'tab';
    $handler->display->display_options['menu']['title'] = 'Year';
    $handler->display->display_options['menu']['weight'] = '4';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
	
  }
}

