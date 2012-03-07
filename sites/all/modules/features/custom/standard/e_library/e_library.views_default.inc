<?php
/**
 * @file
 * e_library.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function e_library_views_default_views() {
  $export = array();


$view = new view;
$view->name = 'e_library';
$view->description = 'A list of all content, by letter.';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'E Library';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'E-Library';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = 36;
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'extension' => 'extension',
  'title' => 'title',
  'name' => 'name',
  'changed' => 'changed',
  'count' => 'count',
);
$handler->display->display_options['style_options']['default'] = 'changed';
$handler->display->display_options['style_options']['info'] = array(
  'extension' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'changed' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'count' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
$handler->display->display_options['style_options']['override'] = 1;
$handler->display->display_options['style_options']['sticky'] = 0;
$handler->display->display_options['style_options']['empty_table'] = 0;
/* Header: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = '<h2>Browse library of document</h2>';
$handler->display->display_options['header']['area']['format'] = 'full_html';
$handler->display->display_options['header']['area']['tokenize'] = 0;
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Relationship: File Usage: File */
$handler->display->display_options['relationships']['node_to_file']['id'] = 'node_to_file';
$handler->display->display_options['relationships']['node_to_file']['table'] = 'file_usage';
$handler->display->display_options['relationships']['node_to_file']['field'] = 'node_to_file';
$handler->display->display_options['relationships']['node_to_file']['required'] = 0;
/* Field: File: Mime type */
$handler->display->display_options['fields']['filemime']['id'] = 'filemime';
$handler->display->display_options['fields']['filemime']['table'] = 'file_managed';
$handler->display->display_options['fields']['filemime']['field'] = 'filemime';
$handler->display->display_options['fields']['filemime']['relationship'] = 'node_to_file';
$handler->display->display_options['fields']['filemime']['label'] = 'File type';
$handler->display->display_options['fields']['filemime']['exclude'] = TRUE;
$handler->display->display_options['fields']['filemime']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['external'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['filemime']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['filemime']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['trim'] = 0;
$handler->display->display_options['fields']['filemime']['alter']['html'] = 0;
$handler->display->display_options['fields']['filemime']['element_label_colon'] = 1;
$handler->display->display_options['fields']['filemime']['element_default_classes'] = 1;
$handler->display->display_options['fields']['filemime']['hide_empty'] = 0;
$handler->display->display_options['fields']['filemime']['empty_zero'] = 0;
$handler->display->display_options['fields']['filemime']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['filemime']['link_to_file'] = 0;
$handler->display->display_options['fields']['filemime']['filemime_image'] = 1;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['title']['alter']['text'] = '[filemime] [title]';
$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title']['alter']['external'] = 0;
$handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title']['alter']['html'] = 0;
$handler->display->display_options['fields']['title']['element_label_colon'] = 1;
$handler->display->display_options['fields']['title']['element_default_classes'] = 1;
$handler->display->display_options['fields']['title']['hide_empty'] = 0;
$handler->display->display_options['fields']['title']['empty_zero'] = 0;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['title']['link_to_node'] = 1;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Author';
$handler->display->display_options['fields']['name']['link_to_user'] = 1;
/* Field: Content: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['label'] = 'Last update';
$handler->display->display_options['fields']['changed']['date_format'] = 'large';
/* Field: File Usage: Use count */
$handler->display->display_options['fields']['count']['id'] = 'count';
$handler->display->display_options['fields']['count']['table'] = 'file_usage';
$handler->display->display_options['fields']['count']['field'] = 'count';
$handler->display->display_options['fields']['count']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['count']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['count']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['count']['alter']['external'] = 0;
$handler->display->display_options['fields']['count']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['count']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['count']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['count']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['count']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['count']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['count']['alter']['trim'] = 0;
$handler->display->display_options['fields']['count']['alter']['html'] = 0;
$handler->display->display_options['fields']['count']['element_label_colon'] = 1;
$handler->display->display_options['fields']['count']['element_default_classes'] = 1;
$handler->display->display_options['fields']['count']['hide_empty'] = 0;
$handler->display->display_options['fields']['count']['empty_zero'] = 0;
$handler->display->display_options['fields']['count']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['count']['format_plural'] = 0;
/* Contextual filter: Broken/missing handler */
$handler->display->display_options['arguments']['group']['id'] = 'group';
$handler->display->display_options['arguments']['group']['table'] = 'og_membership';
$handler->display->display_options['arguments']['group']['field'] = 'group';
$handler->display->display_options['arguments']['group']['relationship'] = 'og_membership_rel';
$handler->display->display_options['arguments']['group']['default_action'] = 'default';
$handler->display->display_options['arguments']['group']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['group']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['group']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['group']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['group']['summary_options']['items_per_page'] = '25';
/* Contextual filter: Content: Title */
$handler->display->display_options['arguments']['title']['id'] = 'title';
$handler->display->display_options['arguments']['title']['table'] = 'node';
$handler->display->display_options['arguments']['title']['field'] = 'title';
$handler->display->display_options['arguments']['title']['default_action'] = 'default';
$handler->display->display_options['arguments']['title']['exception']['title_enable'] = 1;
$handler->display->display_options['arguments']['title']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['title']['default_argument_options']['argument'] = 'a';
$handler->display->display_options['arguments']['title']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['title']['specify_validation'] = 1;
$handler->display->display_options['arguments']['title']['limit'] = '1';
$handler->display->display_options['arguments']['title']['case'] = 'upper';
$handler->display->display_options['arguments']['title']['path_case'] = 'lower';
$handler->display->display_options['arguments']['title']['transform_dash'] = 0;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'document' => 'document',
);
$handler->display->display_options['filters']['type']['group'] = 0;
/* Filter criterion: Workbench Moderation: Published */
$handler->display->display_options['filters']['published']['id'] = 'published';
$handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['published']['field'] = 'published';
$handler->display->display_options['filters']['published']['value'] = '1';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['defaults']['arguments'] = FALSE;
$handler->display->display_options['path'] = 'e_library';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'E-library';
$handler->display->display_options['menu']['weight'] = '15';
$handler->display->display_options['menu']['name'] = 'main-menu';
$handler->display->display_options['menu']['context'] = 0;

/* Display: Attachment */
$handler = $view->new_display('attachment', 'Attachment', 'attachment');
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['defaults']['header'] = FALSE;
/* Header: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = 'Attachment header';
$handler->display->display_options['header']['area']['format'] = 'full_html';
$handler->display->display_options['header']['area']['tokenize'] = 0;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Contextual filter: Content: Title */
$handler->display->display_options['arguments']['title']['id'] = 'title';
$handler->display->display_options['arguments']['title']['table'] = 'node';
$handler->display->display_options['arguments']['title']['field'] = 'title';
$handler->display->display_options['arguments']['title']['default_action'] = 'summary';
$handler->display->display_options['arguments']['title']['exception']['title_enable'] = 1;
$handler->display->display_options['arguments']['title']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['title']['default_argument_options']['argument'] = 'a';
$handler->display->display_options['arguments']['title']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['title']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['title']['summary']['format'] = 'unformatted_summary';
$handler->display->display_options['arguments']['title']['summary_options']['base_path'] = 'community/%1/e_library';
$handler->display->display_options['arguments']['title']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['title']['summary_options']['inline'] = '1';
$handler->display->display_options['arguments']['title']['summary_options']['separator'] = ' | ';
$handler->display->display_options['arguments']['title']['specify_validation'] = 1;
$handler->display->display_options['arguments']['title']['glossary'] = 0;
$handler->display->display_options['arguments']['title']['limit'] = '1';
$handler->display->display_options['arguments']['title']['case'] = 'upper';
$handler->display->display_options['arguments']['title']['path_case'] = 'lower';
$handler->display->display_options['arguments']['title']['transform_dash'] = 0;
$handler->display->display_options['arguments']['title']['break_phrase'] = 0;
$handler->display->display_options['displays'] = array(
  'default' => 0,
  'page' => 0,
);
$handler->display->display_options['attachment_position'] = 'both';
$handler->display->display_options['inherit_arguments'] = 0;
$translatables['e_library'] = array(
  t('Master'),
  t('E-Library'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('<h2>Browse library of document</h2>'),
  t('author'),
  t('File'),
  t('File type'),
  t('Title'),
  t('[filemime] [title]'),
  t('Author'),
  t('Last update'),
  t('Use count'),
  t('.'),
  t(','),
  t('All'),
  t('Page'),
  t('Attachment'),
  t('Attachment header'),
);

  
  
  $export['e_library'] = $view;

  return $export;
}






































































