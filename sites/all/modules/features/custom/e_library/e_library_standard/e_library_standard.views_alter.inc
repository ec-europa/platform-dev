<?php
/**
* Implementation of hook_views_default_views_alter().
*/
function e_library_standard_views_default_views_alter(&$views) {
  if (array_key_exists('e_library', $views)) {
    $view=$views['e_library'];

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page');
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['path'] = 'e_library';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'E-library';
    $handler->display->display_options['menu']['weight'] = '15';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;

    /* Filter criterion: Content: Media tags (field_media_tags) */
    $handler->display->display_options['filters']['field_media_tags_tid']['id'] = 'field_media_tags_tid';
    $handler->display->display_options['filters']['field_media_tags_tid']['table'] = 'field_data_field_media_tags';
    $handler->display->display_options['filters']['field_media_tags_tid']['field'] = 'field_media_tags_tid';
    $handler->display->display_options['filters']['field_media_tags_tid']['exposed'] = TRUE;
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['operator_id'] = 'field_media_tags_tid_op';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['label'] = 'Media tags';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['operator'] = 'field_media_tags_tid_op';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['identifier'] = 'field_media_tags_tid';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['remember_roles'] = array(
      2 => '2',
      1 => 0,
      3 => 0,
      4 => 0,
      5 => 0,
    );
    $handler->display->display_options['filters']['field_media_tags_tid']['type'] = 'select';
    $handler->display->display_options['filters']['field_media_tags_tid']['vocabulary'] = 'media_tags';
    $handler->display->display_options['filters']['field_media_tags_tid']['hierarchy'] = 1;
  }
}



































































