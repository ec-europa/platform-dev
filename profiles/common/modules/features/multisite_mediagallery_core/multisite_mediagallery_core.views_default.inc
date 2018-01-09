<?php

/**
 * @file
 * multisite_mediagallery_core.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function multisite_mediagallery_core_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'galleries';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'galleries';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Galleries';
  $handler->display->display_options['css_class'] = 'grid4';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Picture upload */
  $handler->display->display_options['fields']['field_picture_upload']['id'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['table'] = 'field_data_field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['field'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['label'] = '';
  $handler->display->display_options['fields']['field_picture_upload']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['text'] = '<div class="galleries-item-wrapper">
  [field_picture_upload]
  </div>';
  $handler->display->display_options['fields']['field_picture_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_picture_upload']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_picture_upload']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_picture_upload']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_picture_upload']['delta_reversed'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gallerymedia' => 'gallerymedia',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Published */
  $handler->display->display_options['filters']['published']['id'] = 'published';
  $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['published']['field'] = 'published';
  $handler->display->display_options['filters']['published']['value'] = '1';
  $handler->display->display_options['filters']['published']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Video upload */
  $handler->display->display_options['fields']['field_video_upload']['id'] = 'field_video_upload';
  $handler->display->display_options['fields']['field_video_upload']['table'] = 'field_data_field_video_upload';
  $handler->display->display_options['fields']['field_video_upload']['field'] = 'field_video_upload';
  $handler->display->display_options['fields']['field_video_upload']['label'] = '';
  $handler->display->display_options['fields']['field_video_upload']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_video_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_video_upload']['empty'] = '[Empty_gallery]';
  $handler->display->display_options['fields']['field_video_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_video_upload']['type'] = 'video_formatter_thumbnail';
  $handler->display->display_options['fields']['field_video_upload']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_video_upload']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_video_upload']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_video_upload']['delta_reversed'] = TRUE;
  /* Field: Content: Picture upload */
  $handler->display->display_options['fields']['field_picture_upload']['id'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['table'] = 'field_data_field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['field'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['label'] = '';
  $handler->display->display_options['fields']['field_picture_upload']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_picture_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['empty'] = '[Empty_gallery]';
  $handler->display->display_options['fields']['field_picture_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_picture_upload']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_picture_upload']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_picture_upload']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_picture_upload']['delta_reversed'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="galleries-item-wrapper">
  [field_picture_upload][field_video_upload]
  </div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<div id="nb_items">[nid]</div>';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gallerymedia' => 'gallerymedia',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Published */
  $handler->display->display_options['filters']['published']['id'] = 'published';
  $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['published']['field'] = 'published';
  $handler->display->display_options['filters']['published']['value'] = '1';
  $handler->display->display_options['filters']['published']['group'] = 1;
  $handler->display->display_options['path'] = 'galleries';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Galleries';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Latest Media block */
  $handler = $view->new_display('block', 'Latest Media block', 'medias_block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'item';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h4';
  $handler->display->display_options['fields']['title']['element_class'] = 'carousel-caption';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Field: Content: Picture upload */
  $handler->display->display_options['fields']['field_picture_upload']['id'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['table'] = 'field_data_field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['field'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['label'] = '';
  $handler->display->display_options['fields']['field_picture_upload']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_picture_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['empty'] = '[Empty_gallery]';
  $handler->display->display_options['fields']['field_picture_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_picture_upload']['settings'] = array(
    'image_style' => 'landscape',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_picture_upload']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_picture_upload']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_picture_upload']['delta_reversed'] = TRUE;
  /* Field: Content: Video upload */
  $handler->display->display_options['fields']['field_video_upload']['id'] = 'field_video_upload';
  $handler->display->display_options['fields']['field_video_upload']['table'] = 'field_data_field_video_upload';
  $handler->display->display_options['fields']['field_video_upload']['field'] = 'field_video_upload';
  $handler->display->display_options['fields']['field_video_upload']['label'] = '';
  $handler->display->display_options['fields']['field_video_upload']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_video_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_video_upload']['empty'] = '[Empty_gallery]';
  $handler->display->display_options['fields']['field_video_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_video_upload']['type'] = 'video_formatter_thumbnail';
  $handler->display->display_options['fields']['field_video_upload']['settings'] = array(
    'image_style' => 'landscape',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_video_upload']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_video_upload']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_picture_upload][field_video_upload]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gallerymedia' => 'gallerymedia',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Published */
  $handler->display->display_options['filters']['published']['id'] = 'published';
  $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['published']['field'] = 'published';
  $handler->display->display_options['filters']['published']['value'] = '1';
  $handler->display->display_options['filters']['published']['group'] = 1;
  /* Filter criterion: Content: Picture upload (field_picture_upload:fid) */
  $handler->display->display_options['filters']['field_picture_upload_fid']['id'] = 'field_picture_upload_fid';
  $handler->display->display_options['filters']['field_picture_upload_fid']['table'] = 'field_data_field_picture_upload';
  $handler->display->display_options['filters']['field_picture_upload_fid']['field'] = 'field_picture_upload_fid';
  $handler->display->display_options['filters']['field_picture_upload_fid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_picture_upload_fid']['group'] = 2;
  /* Filter criterion: Content: Video upload (field_video_upload:fid) */
  $handler->display->display_options['filters']['field_video_upload_fid']['id'] = 'field_video_upload_fid';
  $handler->display->display_options['filters']['field_video_upload_fid']['table'] = 'field_data_field_video_upload';
  $handler->display->display_options['filters']['field_video_upload_fid']['field'] = 'field_video_upload_fid';
  $handler->display->display_options['filters']['field_video_upload_fid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_video_upload_fid']['group'] = 2;

  $export['galleries'] = $view;

  return $export;
}
