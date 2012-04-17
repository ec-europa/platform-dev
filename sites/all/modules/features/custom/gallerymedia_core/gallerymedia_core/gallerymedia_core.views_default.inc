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
  $handler->display->display_options['title'] = 'galleries';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: multimedia */
  $handler->display->display_options['fields']['field_multimedia']['id'] = 'field_multimedia';
  $handler->display->display_options['fields']['field_multimedia']['table'] = 'field_data_field_multimedia';
  $handler->display->display_options['fields']['field_multimedia']['field'] = 'field_multimedia';
  $handler->display->display_options['fields']['field_multimedia']['label'] = '';
  $handler->display->display_options['fields']['field_multimedia']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['text'] = '[field_multimedia-fid]
[title]
[field_multimedia] 
[field_multimedia-display]
 [field_multimedia-description]';
  $handler->display->display_options['fields']['field_multimedia']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['field_multimedia']['alter']['path'] = 'content/[title]';
  $handler->display->display_options['fields']['field_multimedia']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_multimedia']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_multimedia']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_multimedia']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_multimedia']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_multimedia']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_multimedia']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
  $handler->display->display_options['fields']['field_multimedia']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_multimedia']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_multimedia']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_multimedia']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_multimedia']['field_api_classes'] = 0;
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
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'galleries';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Galleries';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['galleries'] = array(
    t('Master'),
    t('galleries'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('[field_multimedia-fid]
[title]
[field_multimedia] 
[field_multimedia-display]
 [field_multimedia-description]'),
    t('content/[title]'),
    t('Page'),
  );
  $export['galleries'] = $view;

  return $export;
}
