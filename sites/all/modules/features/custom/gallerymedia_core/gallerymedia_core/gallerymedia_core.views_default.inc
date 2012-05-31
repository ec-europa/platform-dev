<?php
/**
 * @file
 * gallerymedia_core.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gallerymedia_core_views_default_views() {
  $export = array();

  $view = new view;
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
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['fill_single_line'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  /* Field: Content: Picture upload */
  $handler->display->display_options['fields']['field_picture_upload']['id'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['table'] = 'field_data_field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['field'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['label'] = '';
  $handler->display->display_options['fields']['field_picture_upload']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['text'] = '<div class="galleries-item-wrapper">
[field_picture_upload]
</div>';
  $handler->display->display_options['fields']['field_picture_upload']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_picture_upload']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_picture_upload']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_picture_upload']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_picture_upload']['delta_reversed'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['body']['alter']['html'] = 1;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gallerymedia' => 'gallerymedia',
  );
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  $handler->display->display_options['filters']['language']['group'] = 2;
  /* Filter criterion: Content translation: Translation set node ID */
  $handler->display->display_options['filters']['tnid']['id'] = 'tnid';
  $handler->display->display_options['filters']['tnid']['table'] = 'node';
  $handler->display->display_options['filters']['tnid']['field'] = 'tnid';
  $handler->display->display_options['filters']['tnid']['value']['value'] = '0';
  $handler->display->display_options['filters']['tnid']['group'] = 2;


  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Picture upload */
  $handler->display->display_options['fields']['field_picture_upload']['id'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['table'] = 'field_data_field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['field'] = 'field_picture_upload';
  $handler->display->display_options['fields']['field_picture_upload']['label'] = '';
  $handler->display->display_options['fields']['field_picture_upload']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['text'] = '<div class="galleries-item-wrapper">
[field_picture_upload]
</div>';
  $handler->display->display_options['fields']['field_picture_upload']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_picture_upload']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['empty'] = '<img src="sites/default/files/styles/square_thumbnail/public/default_images/empty_gallery.png"/>';
  $handler->display->display_options['fields']['field_picture_upload']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_picture_upload']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_picture_upload']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_picture_upload']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_picture_upload']['delta_reversed'] = 1;
  $handler->display->display_options['fields']['field_picture_upload']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_picture_upload']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['body']['alter']['html'] = 1;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  $handler->display->display_options['path'] = 'galleries';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Galleries';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['galleries'] = array(
    t('Master'),
    t('Galleries'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('<div class="galleries-item-wrapper">
[field_picture_upload]
</div>'),
    t('Page'),
    t('<div class="galleries-item-wrapper">
[field_picture_upload]
</div>'),
    t('<img src="sites/default/files/styles/square_thumbnail/public/default_images/empty_gallery.png"/>'),
  );
  $export['galleries'] = $view;

  return $export;
}
