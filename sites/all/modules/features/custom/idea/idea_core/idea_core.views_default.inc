<?php
/**
 * @file
 * idea_core.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function idea_core_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'idea_list';
  $view->description = 'Show all content (nodes) of a group.';
  $view->tag = 'og';
  $view->base_table = 'node';
  $view->human_name = 'Idea list';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Ideas';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'name' => 'name',
    'field_categories' => 'field_categories',
    'field_status' => 'field_status',
    'field_watching' => 'field_watching',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
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
    'field_categories' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_watching' => array(
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
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There is no content in this group.';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Field: Content: categories */
  $handler->display->display_options['fields']['field_categories']['id'] = 'field_categories';
  $handler->display->display_options['fields']['field_categories']['table'] = 'field_data_field_categories';
  $handler->display->display_options['fields']['field_categories']['field'] = 'field_categories';
  $handler->display->display_options['fields']['field_categories']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_categories']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_categories']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_categories']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_categories']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_categories']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_categories']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_categories']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_categories']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_categories']['field_api_classes'] = 0;
  /* Field: Content: status */
  $handler->display->display_options['fields']['field_status']['id'] = 'field_status';
  $handler->display->display_options['fields']['field_status']['table'] = 'field_data_field_status';
  $handler->display->display_options['fields']['field_status']['field'] = 'field_status';
  $handler->display->display_options['fields']['field_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_status']['field_api_classes'] = 0;
  /* Field: Content: Idea we are watching */
  $handler->display->display_options['fields']['field_watching']['id'] = 'field_watching';
  $handler->display->display_options['fields']['field_watching']['table'] = 'field_data_field_watching';
  $handler->display->display_options['fields']['field_watching']['field'] = 'field_watching';
  $handler->display->display_options['fields']['field_watching']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_watching']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_watching']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_watching']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_watching']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_watching']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_watching']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_watching']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_watching']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_watching']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'idea' => 'idea',
  );

  $translatables['idea_list'] = array(
    t('Defaults'),
    t('Ideas'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('There is no content in this group.'),
    t('author'),
    t('Title'),
    t('Name'),
    t('categories'),
    t('status'),
    t('Idea we are watching'),
    t('Page'),
  );
  $export['idea_list'] = $view;

  return $export;
}
