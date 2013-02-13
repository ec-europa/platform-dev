<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function links_og_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('links', $views)) {
    $view=$views['links'];

    /* Display: Master */
    $handler = $view->display['default']->handler;
    $handler->display->display_options['access']['type'] = 'og_context';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['path'] = 'community/links';
    $handler->display->display_options['menu']['type'] = 'none';



  }
}
