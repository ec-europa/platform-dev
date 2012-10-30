<?php
/**
* Implementation of hook_views_default_views_alter().
*/
function media_library_standard_views_default_views_alter(&$views) {
  if (array_key_exists('media_library', $views)) {
    $view=$views['media_library'];

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page');
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['path'] = 'media_library';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Media-library';
    $handler->display->display_options['menu']['weight'] = '15';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;

  }
}



































































