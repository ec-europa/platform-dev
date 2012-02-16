<?php
/**
 * @file
 * group_forum.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function group_forum_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'forum_thread_list';
  $view->description = 'This list is about the forum thread embed within a room';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Forum Thread List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Forum Thread List';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'new_comments' => 'name',
    'name' => 'name',
    'title' => 'title',
    'created' => 'created',
    'comment_count' => 'comment_count',
    'last_comment_name' => 'last_comment_name',
    'last_comment_timestamp' => 'last_comment_timestamp',
  );
  $handler->display->display_options['style_options']['default'] = 'last_comment_timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'new_comments' => array(
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
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'comment_count' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_comment_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_comment_timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
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
  $handler->display->display_options['header']['area']['content'] = 'header content';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are not yet any thread in this room';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 1;
  /* Field: Content: New comments */
  $handler->display->display_options['fields']['new_comments']['id'] = 'new_comments';
  $handler->display->display_options['fields']['new_comments']['table'] = 'node';
  $handler->display->display_options['fields']['new_comments']['field'] = 'new_comments';
  $handler->display->display_options['fields']['new_comments']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['external'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['new_comments']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['new_comments']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['html'] = 0;
  $handler->display->display_options['fields']['new_comments']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['new_comments']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['new_comments']['hide_empty'] = 0;
  $handler->display->display_options['fields']['new_comments']['empty_zero'] = 0;
  $handler->display->display_options['fields']['new_comments']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['new_comments']['format_plural'] = 0;
  $handler->display->display_options['fields']['new_comments']['link_to_comment'] = 1;
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['external'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['comment_count']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['comment_count']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['html'] = 0;
  $handler->display->display_options['fields']['comment_count']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['comment_count']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['comment_count']['hide_empty'] = 0;
  $handler->display->display_options['fields']['comment_count']['empty_zero'] = 0;
  $handler->display->display_options['fields']['comment_count']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['comment_count']['format_plural'] = 0;
  /* Field: Content: Last comment author */
  $handler->display->display_options['fields']['last_comment_name']['id'] = 'last_comment_name';
  $handler->display->display_options['fields']['last_comment_name']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_comment_name']['field'] = 'last_comment_name';
  $handler->display->display_options['fields']['last_comment_name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['last_comment_name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['last_comment_name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['last_comment_name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['last_comment_name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['last_comment_name']['hide_alter_empty'] = 1;
  /* Field: Content: Last comment time */
  $handler->display->display_options['fields']['last_comment_timestamp']['id'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_comment_timestamp']['field'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['external'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['html'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['hide_empty'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['empty_zero'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['date_format'] = 'medium';
  /* Sort criterion: Content: Last comment time */
  $handler->display->display_options['sorts']['last_comment_timestamp']['id'] = 'last_comment_timestamp';
  $handler->display->display_options['sorts']['last_comment_timestamp']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['last_comment_timestamp']['field'] = 'last_comment_timestamp';
  $handler->display->display_options['sorts']['last_comment_timestamp']['order'] = 'DESC';
  $handler->display->display_options['sorts']['last_comment_timestamp']['granularity'] = 'minute';
  /* Contextual filter: Content: Forum Room (field_forum_room) */
  $handler->display->display_options['arguments']['field_forum_room_nid']['id'] = 'field_forum_room_nid';
  $handler->display->display_options['arguments']['field_forum_room_nid']['table'] = 'field_data_field_forum_room';
  $handler->display->display_options['arguments']['field_forum_room_nid']['field'] = 'field_forum_room_nid';
  $handler->display->display_options['arguments']['field_forum_room_nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_forum_room_nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_forum_room_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_forum_room_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_forum_room_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_forum_room_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_forum_room_nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_forum_room_nid']['validate_options']['types'] = array(
    'forum_room' => 'forum_room',
  );
  $handler->display->display_options['arguments']['field_forum_room_nid']['validate_options']['access'] = 0;
  $handler->display->display_options['arguments']['field_forum_room_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_forum_room_nid']['not'] = 0;
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
    'forum_thread' => 'forum_thread',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = 0;
  $handler->display->display_options['filters']['title']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_forum_threads');
  $handler->display->display_options['path'] = 'NONE/%/thread';
  $translatables['forum_thread_list'] = array(
    t('Master'),
    t('Forum Thread List'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('header content'),
    t('There are not yet any thread in this room'),
    t('author'),
    t('New comments'),
    t('.'),
    t(','),
    t('Name'),
    t('Title'),
    t('Post date'),
    t('Comment count'),
    t('Last comment author'),
    t('Last comment time'),
    t('All'),
    t('Page'),
  );
  $export['forum_thread_list'] = $view;

  return $export;
}
