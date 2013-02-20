<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function events_og_views_default_views_alter(&$views) {
  if (array_key_exists('calendar', $views)) {
    $view=$views['calendar'];



    $handler = $view->display['month']->handler;
    unset($handler->display->display_options['path']);
    unset($handler->display->display_options['menu']);
    unset($handler->display->display_options['tab_options']);
    
  }
}

