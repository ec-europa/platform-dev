<?php

/**
 * Implementation of hook_views_default_views().
 */
function ideation_views_default_views() {
  $views = array();

  // Exported view: ideas_comments
  $view = new view;
  $view->name = 'ideas_comments';
  $view->description = '';
  $view->tag = 'ideas';
  $view->base_table = 'comment';
  $view->human_name = 'Ideas: Recent Ideas Comments';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'ideas';
  $handler->display->display_options['style_options']['class'] = 'ideas';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Comment: Node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'comment';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Field: Fields: comment_body */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_comment_body';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['label'] = '';
  $handler->display->display_options['fields']['entity_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id']['element_type'] = 'div';
  $handler->display->display_options['fields']['entity_id']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['entity_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id']['empty_zero'] = 0;
  /* Field: Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'nid';
  $handler->display->display_options['filters']['type']['value'] = array(
    'idea_site' => 'idea_site',
  );

  /* Display: Block: Recent Ideas Comments */
  $handler = $view->new_display('block', 'Block: Recent Ideas Comments', 'block_ideas_comments');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent Ideas Comments';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Comment: Node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'comment';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Fields: comment_body */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_comment_body';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['label'] = '';
  $handler->display->display_options['fields']['entity_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id']['element_type'] = 'div';
  $handler->display->display_options['fields']['entity_id']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['entity_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id']['empty_zero'] = 0;
  /* Field: Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'nid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Node: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'nid';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_type'] = '0';
  $handler->display->display_options['fields']['created']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $translatables['ideas_comments'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort By'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Node'),
    t('Title'),
    t('Block: Recent Ideas Comments'),
    t('Recent Ideas Comments'),
  );

  $views[$view->name] = $view;

  // Exported view: ideas_listing
  $view = new view;
  $view->name = 'ideas_listing';
  $view->description = '';
  $view->tag = 'ideas';
  $view->base_table = 'node';
  $view->human_name = 'Ideas: Listing';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Ideas';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = 1;
  $handler->display->display_options['row_options']['comments'] = 0;
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'idea_site' => 'idea_site',
  );
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['label'] = 'Keyword';
  $handler->display->display_options['filters']['keys']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['single'] = TRUE;
  /* Filter: Fields: field_idea_status (field_idea_status) */
  $handler->display->display_options['filters']['field_idea_status_value']['id'] = 'field_idea_status_value';
  $handler->display->display_options['filters']['field_idea_status_value']['table'] = 'field_data_field_idea_status';
  $handler->display->display_options['filters']['field_idea_status_value']['field'] = 'field_idea_status_value';
  $handler->display->display_options['filters']['field_idea_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_idea_status_value']['expose']['operator'] = 'field_idea_status_value_op';
  $handler->display->display_options['filters']['field_idea_status_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_idea_status_value']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['field_idea_status_value']['expose']['identifier'] = 'field_idea_status_value';
  $handler->display->display_options['filters']['field_idea_status_value']['expose']['single'] = 0;
  $handler->display->display_options['filters']['field_idea_status_value']['expose']['reduce'] = 0;
  /* Filter: Fields: field_idea_categories (field_idea_categories) */
  $handler->display->display_options['filters']['field_idea_categories_value']['id'] = 'field_idea_categories_value';
  $handler->display->display_options['filters']['field_idea_categories_value']['table'] = 'field_data_field_idea_categories';
  $handler->display->display_options['filters']['field_idea_categories_value']['field'] = 'field_idea_categories_value';
  $handler->display->display_options['filters']['field_idea_categories_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_idea_categories_value']['expose']['operator'] = 'field_idea_categories_value_op';
  $handler->display->display_options['filters']['field_idea_categories_value']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['field_idea_categories_value']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['field_idea_categories_value']['expose']['identifier'] = 'field_idea_categories_value';
  $handler->display->display_options['filters']['field_idea_categories_value']['expose']['reduce'] = 0;
  /* Filter: Fields: field_idea_watch (field_idea_watch) */
  $handler->display->display_options['filters']['field_idea_watch_value']['id'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['table'] = 'field_data_field_idea_watch';
  $handler->display->display_options['filters']['field_idea_watch_value']['field'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['operator'] = 'field_idea_watch_value_op';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['label'] = 'Watching';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['identifier'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['reduce'] = 0;

  /* Display: Page: Ideas by Recent */
  $handler = $view->new_display('page', 'Page: Ideas by Recent', 'page_ideas_recent');
  $handler->display->display_options['defaults']['exposed_block'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'ideas/recent';
  $translatables['ideas_listing'] = array(
    t('Defaults'),
    t('Ideas'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort By'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Keyword'),
    t('Status'),
    t('Category'),
    t('Watching'),
    t('Page: Ideas by Recent'),
  );

  $views[$view->name] = $view;

  // Exported view: ideas_watch
  $view = new view;
  $view->name = 'ideas_watch';
  $view->description = '';
  $view->tag = 'ideas';
  $view->base_table = 'node';
  $view->human_name = 'Ideas We\'re Watching';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['html'] = 0;
  $handler->display->display_options['fields']['picture']['element_label_type'] = '0';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['picture']['hide_empty'] = 0;
  $handler->display->display_options['fields']['picture']['empty_zero'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Node: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_type'] = '0';
  $handler->display->display_options['fields']['created']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  /* Filter: Fields: field_idea_watch (field_idea_watch) */
  $handler->display->display_options['filters']['field_idea_watch_value']['id'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['table'] = 'field_data_field_idea_watch';
  $handler->display->display_options['filters']['field_idea_watch_value']['field'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['operator'] = 'field_idea_watch_value_op';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['label'] = 'Fields: field_idea_watch (field_idea_watch)';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['identifier'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['optional'] = TRUE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['single'] = TRUE;
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_ideas_watch');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Idea\'s We\'re Watching';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter: Fields: field_idea_watch (field_idea_watch) */
  $handler->display->display_options['filters']['field_idea_watch_value']['id'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['table'] = 'field_data_field_idea_watch';
  $handler->display->display_options['filters']['field_idea_watch_value']['field'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['operator'] = 'field_idea_watch_value_op';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['label'] = 'Fields: field_idea_watch (field_idea_watch)';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['identifier'] = 'field_idea_watch_value';
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['optional'] = TRUE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_idea_watch_value']['expose']['single'] = TRUE;
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $translatables['ideas_watch'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort By'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Fields: field_idea_watch (field_idea_watch)'),
    t('Block'),
    t('Idea\'s We\'re Watching'),
  );

  $views[$view->name] = $view;

  return $views;
}
