<?php
/**
 * @file
 * f_a_q.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function f_a_q_views_default_views() {
  $export = array();

$view = new view;
$view->name = 'faq';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'F.A.Q';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'F.A.Q';
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '30';
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['style_options']['type'] = 'ol';
$handler->display->display_options['style_options']['class'] = 'nav nav-tabs nav-stacked';
$handler->display->display_options['row_plugin'] = 'fields';
/* Header: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = '<h2>Quick answer to common questions</h2>';
$handler->display->display_options['header']['area']['format'] = 'full_html';
$handler->display->display_options['header']['area']['tokenize'] = 0;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['title']['alter']['make_link'] = 1;
$handler->display->display_options['fields']['title']['alter']['path'] = '/';
$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title']['alter']['external'] = 0;
$handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['title']['alter']['link_class'] = 'views-field-title';
$handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title']['alter']['html'] = 0;
$handler->display->display_options['fields']['title']['element_type'] = '0';
$handler->display->display_options['fields']['title']['element_label_type'] = '0';
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
$handler->display->display_options['fields']['title']['element_default_classes'] = 0;
$handler->display->display_options['fields']['title']['hide_empty'] = 0;
$handler->display->display_options['fields']['title']['empty_zero'] = 0;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['title']['link_to_node'] = 0;
/* Field: Node: Edit link */
$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['label'] = '';
$handler->display->display_options['fields']['edit_node']['exclude'] = TRUE;
$handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
$handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
$handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['edit_node']['element_default_classes'] = 1;
$handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
$handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
$handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['edit_node']['text'] = 'Edit this item';
/* Field: Content: Body */
$handler->display->display_options['fields']['body']['id'] = 'body';
$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
$handler->display->display_options['fields']['body']['field'] = 'body';
$handler->display->display_options['fields']['body']['label'] = '';
$handler->display->display_options['fields']['body']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['body']['alter']['text'] = '[edit_node][body]
';
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
/* Field: Content: Tags */
$handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
$handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
$handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
$handler->display->display_options['fields']['field_tags']['label'] = '';
$handler->display->display_options['fields']['field_tags']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['external'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['field_tags']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['field_tags']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['trim'] = 0;
$handler->display->display_options['fields']['field_tags']['alter']['html'] = 0;
$handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_tags']['element_default_classes'] = 1;
$handler->display->display_options['fields']['field_tags']['hide_empty'] = 0;
$handler->display->display_options['fields']['field_tags']['empty_zero'] = 0;
$handler->display->display_options['fields']['field_tags']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['field_tags']['group_rows'] = 1;
$handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
$handler->display->display_options['fields']['field_tags']['delta_reversed'] = 0;
$handler->display->display_options['fields']['field_tags']['delta_first_last'] = 0;
$handler->display->display_options['fields']['field_tags']['field_api_classes'] = 0;
/* Sort criterion: Content: Post date */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'node';
$handler->display->display_options['sorts']['created']['field'] = 'created';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 0;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'f_a_q' => 'f_a_q',
);
$handler->display->display_options['filters']['type']['group'] = 0;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'faq';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'F.A.Q';
$handler->display->display_options['menu']['weight'] = '50';
$handler->display->display_options['menu']['name'] = 'main-menu';
$translatables['faq'] = array(
  t('Master'),
  t('F.A.Q'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('<h2>Quick answer to common questions</h2>'),
  t('/'),
  t('Edit this item'),
  t('[edit_node][body]
'),
  t('Page'),
);

  $export['faq'] = $view;

  return $export;
}
