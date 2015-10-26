<?php
/**
 * @file
 * nexteuropa_newsroom.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function nexteuropa_newsroom_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'newsletter_subscription';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Newsletter subscription';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Newsletter subscription';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Newsroom Service ID */
  $handler->display->display_options['fields']['field_newsroom_service_id']['id'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['table'] = 'field_data_field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['field'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_service_id']['element_label_colon'] = FALSE;
  /* Contextual filter: Taxonomy term: Newsroom Topic (field_newsroom_topic) */
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['id'] = 'field_newsroom_topic_tid';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['table'] = 'field_data_field_newsroom_topic';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['field'] = 'field_newsroom_topic_tid';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_options']['node'] = TRUE;
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['default_argument_options']['vocabularies'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['validate_options']['vocabularies'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['field_newsroom_topic_tid']['validate_options']['type'] = 'tids';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service type (field_service_type) */
  $handler->display->display_options['filters']['field_service_type_value']['id'] = 'field_service_type_value';
  $handler->display->display_options['filters']['field_service_type_value']['table'] = 'field_data_field_service_type';
  $handler->display->display_options['filters']['field_service_type_value']['field'] = 'field_service_type_value';
  $handler->display->display_options['filters']['field_service_type_value']['value'] = 'Newsletter';
  /* Filter criterion: Taxonomy term: Service active (field_service_active) */
  $handler->display->display_options['filters']['field_service_active_value']['id'] = 'field_service_active_value';
  $handler->display->display_options['filters']['field_service_active_value']['table'] = 'field_data_field_service_active';
  $handler->display->display_options['filters']['field_service_active_value']['field'] = 'field_service_active_value';
  $handler->display->display_options['filters']['field_service_active_value']['value'] = 'Active';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['newsletter_subscription'] = array(
    t('Master'),
    t('Newsletter subscription'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Name'),
    t('All'),
    t('Block'),
  );
  $export['newsletter_subscription'] = $view;

  $view = new view();
  $view->name = 'newsroom';
  $view->description = '';
  $view->tag = 'newsroom';
  $view->base_table = 'node';
  $view->human_name = 'Newsroom';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Newsroom';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '60';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '60';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'clearfix';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: embedded_node */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['ui_name'] = 'embedded_node';
  $handler->display->display_options['header']['entity']['empty'] = TRUE;
  $handler->display->display_options['header']['entity']['entity_id'] = '0';
  /* Header: featured */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['ui_name'] = 'featured';
  $handler->display->display_options['header']['view']['empty'] = TRUE;
  $handler->display->display_options['header']['view']['view_to_insert'] = 'newsroom_type_featured_item:block';
  $handler->display->display_options['header']['view']['inherit_arguments'] = TRUE;
  /* Relationship: Content: Newsroom Item Type (field_newsroom_item_type) */
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['id'] = 'field_newsroom_item_type_tid';
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['table'] = 'field_data_field_newsroom_item_type';
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['field'] = 'field_newsroom_item_type_tid';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_newsroom_item_type_tid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['convert_spaces'] = TRUE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['relationship'] = 'field_newsroom_item_type_tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  /* Field: Content: Newsroom Item Type */
  $handler->display->display_options['fields']['field_newsroom_item_type']['id'] = 'field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['table'] = 'field_data_field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['field'] = 'field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_type']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['alter']['path'] = 'newsroom/[name]/!2';
  $handler->display->display_options['fields']['field_newsroom_item_type']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Main Link */
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['id'] = 'field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['table'] = 'field_data_field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['field'] = 'field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['empty'] = '[path]';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['type'] = 'newsroom_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['settings'] = array(
    'display_type' => 'teaser',
  );
  /* Field: Content: Illustrative Image */
  $handler->display->display_options['fields']['field_illustrative_image']['id'] = 'field_illustrative_image';
  $handler->display->display_options['fields']['field_illustrative_image']['table'] = 'field_data_field_illustrative_image';
  $handler->display->display_options['fields']['field_illustrative_image']['field'] = 'field_illustrative_image';
  $handler->display->display_options['fields']['field_illustrative_image']['label'] = '';
  $handler->display->display_options['fields']['field_illustrative_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_illustrative_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_illustrative_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_illustrative_image']['settings'] = array(
    'image_style' => 'newsroom_style',
    'image_link' => 'content',
  );
  /* Field: Entity translation: Title: translated */
  $handler->display->display_options['fields']['title_field_et']['id'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field_et']['field'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['label'] = '';
  $handler->display->display_options['fields']['title_field_et']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_field_et']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title_field_et']['alter']['path'] = '[field_newsroom_item_main_link]';
  $handler->display->display_options['fields']['title_field_et']['element_label_colon'] = FALSE;
  /* Field: Content: Short Title */
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['id'] = 'field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['table'] = 'field_data_field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['field'] = 'field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['path'] = '[field_newsroom_item_main_link]';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['empty'] = '[title_field_et]';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_newsroom_item_date']['id'] = 'field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['field'] = 'field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_date']['settings'] = array(
    'format_type' => 'date_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Venue */
  $handler->display->display_options['fields']['field_newsroom_item_venue']['id'] = 'field_newsroom_item_venue';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['table'] = 'field_data_field_newsroom_item_venue';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['field'] = 'field_newsroom_item_venue';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Read more';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[field_newsroom_item_main_link]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_teaser']['id'] = 'field_teaser';
  $handler->display->display_options['fields']['field_teaser']['table'] = 'field_data_field_teaser';
  $handler->display->display_options['fields']['field_teaser']['field'] = 'field_teaser';
  $handler->display->display_options['fields']['field_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_teaser']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_teaser']['alter']['text'] = '[field_teaser] [nothing]';
  $handler->display->display_options['fields']['field_teaser']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_action'] = 'default';
  $handler->display->display_options['arguments']['term_node_tid_depth']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['exception']['title'] = '';
  $handler->display->display_options['arguments']['term_node_tid_depth']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title'] = '<span class="filter_type">%1</span>';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_options']['argument'] = 'all';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['base_path'] = 'neswroom/';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['vocabularies'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['transform'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '1';
  $handler->display->display_options['arguments']['term_node_tid_depth']['break_phrase'] = TRUE;
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['id'] = 'term_node_tid_depth_1';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['exception']['title'] = '';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['title'] = '<span class="filter_type">%1</span> <span class="filter_topic">%2</span>';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['default_argument_options']['argument'] = 'all';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['validate_options']['vocabularies'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['validate_options']['transform'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['depth'] = '1';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['break_phrase'] = TRUE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
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
    'newsroom_item' => 'newsroom_item',
  );

  /* Display: default_newsroom */
  $handler = $view->new_display('page', 'default_newsroom', 'default_newsroom');
  $handler->display->display_options['path'] = 'newsroom';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['uses_fields'] = TRUE;
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_action'] = 'default';
  $handler->display->display_options['arguments']['term_node_tid_depth']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title'] = '%1';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_options']['argument'] = 'all';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['base_path'] = 'neswroom/';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['vocabularies'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['transform'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '1';
  $handler->display->display_options['arguments']['term_node_tid_depth']['break_phrase'] = TRUE;
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['id'] = 'term_node_tid_depth_1';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['exception']['title'] = '';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['title'] = '%2 in %1';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['default_argument_options']['argument'] = 'all';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['validate_options']['vocabularies'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['depth'] = '1';
  $handler->display->display_options['arguments']['term_node_tid_depth_1']['break_phrase'] = TRUE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'newsroom/%/%/feed';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
    'page' => 'page',
  );

  /* Display: events */
  $handler = $view->new_display('page', 'events', 'events');
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['footer']['area_text_custom']['content'] = '<a href="/digital-agenda/newsroom/!1/!2/previous">Past %1 about %2</a>';
  $handler->display->display_options['footer']['area_text_custom']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Date -  start date (field_newsroom_item_date) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['id'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['field'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['granularity'] = 'second';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['form_type'] = 'date_text';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['default_date'] = 'now';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['id'] = 'field_newsroom_item_date_value2_1';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['group'] = 2;
  $handler->display->display_options['path'] = 'newsroom_events';

  /* Display: previous_events */
  $handler = $view->new_display('page', 'previous_events', 'previous_events');
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['footer']['area_text_custom']['content'] = '<a href="/digital-agenda/newsroom/!1/!2/">Current %1 about %2</a>';
  $handler->display->display_options['footer']['area_text_custom']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['operator'] = '<';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['granularity'] = 'second';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['form_type'] = 'date_text';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['default_date'] = 'now';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Content: Date -  start date (field_newsroom_item_date) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value']['id'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['filters']['field_newsroom_item_date_value']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value']['field'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['filters']['field_newsroom_item_date_value']['operator'] = '<';
  $handler->display->display_options['filters']['field_newsroom_item_date_value']['group'] = 2;
  $handler->display->display_options['filters']['field_newsroom_item_date_value']['default_date'] = 'now';
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['id'] = 'field_newsroom_item_date_value2_1';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['group'] = 2;
  $handler->display->display_options['path'] = 'newsroom_events';

  /* Display: consultation_funding */
  $handler = $view->new_display('page', 'consultation_funding', 'consultation_funding');
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['footer']['area_text_custom']['content'] = '<a href="/digital-agenda/newsroom/!1/!2/previous">Past %1 about %2</a>';
  $handler->display->display_options['footer']['area_text_custom']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Date -  start date (field_newsroom_item_date) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['id'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['field'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['order'] = 'DESC';
  /* Sort criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['granularity'] = 'second';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['default_date'] = 'now';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['id'] = 'field_newsroom_item_date_value2_1';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['group'] = 2;
  $handler->display->display_options['path'] = 'newsroom_consultation_funding';

  /* Display: previous_consultation_funding */
  $handler = $view->new_display('page', 'previous_consultation_funding', 'previous_consultation_funding');
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['footer']['area_text_custom']['content'] = '<a href="/digital-agenda/newsroom/!1/!2">Current %1 about %2</a>';
  $handler->display->display_options['footer']['area_text_custom']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'newsroom_item' => 'newsroom_item',
  );
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['operator'] = '<';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['granularity'] = 'second';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['default_date'] = 'now';
  $handler->display->display_options['path'] = 'newsroom_consultation_funding';

  $export['newsroom'] = $view;

  $view = new view();
  $view->name = 'newsroom_calendar';
  $view->description = 'A multi-dimensional calendar view with back/next navigation.';
  $view->tag = 'newsroom';
  $view->base_table = 'node';
  $view->human_name = 'Newsroom Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '<none>';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'fullcalendar';
  $handler->display->display_options['style_options']['firstDay'] = '1';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<h2>Consult planned events</h2>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Relationship: Content: Newsroom Item Type (field_newsroom_item_type) */
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['id'] = 'field_newsroom_item_type_tid';
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['table'] = 'field_data_field_newsroom_item_type';
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['field'] = 'field_newsroom_item_type_tid';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Content: Main Link */
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['id'] = 'field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['table'] = 'field_data_field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['field'] = 'field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['empty'] = '[path]';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['type'] = 'link_plain';
  /* Field: Content: Teaser only */
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['id'] = 'field_newsroom_teaser_only';
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['table'] = 'field_data_field_newsroom_teaser_only';
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['field'] = 'field_newsroom_teaser_only';
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['alter']['text'] = '[field_newsroom_item_main_link]';
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['empty'] = '[path]';
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_teaser_only']['type'] = 'list_key';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = '[field_newsroom_teaser_only]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Short Title */
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['id'] = 'field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['table'] = 'field_data_field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['field'] = 'field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['path'] = '[field_newsroom_teaser_only]';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['empty'] = '[title]';
  /* Field: Content: All taxonomy terms */
  $handler->display->display_options['fields']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['fields']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['fields']['term_node_tid']['field'] = 'term_node_tid';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_newsroom_item_date']['id'] = 'field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['field'] = 'field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_date']['settings'] = array(
    'format_type' => 'mysql_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Taxonomy term: Listing behavior (field_newsroom_type) */
  $handler->display->display_options['filters']['field_newsroom_type_value']['id'] = 'field_newsroom_type_value';
  $handler->display->display_options['filters']['field_newsroom_type_value']['table'] = 'field_data_field_newsroom_type';
  $handler->display->display_options['filters']['field_newsroom_type_value']['field'] = 'field_newsroom_type_value';
  $handler->display->display_options['filters']['field_newsroom_type_value']['relationship'] = 'field_newsroom_item_type_tid';
  $handler->display->display_options['filters']['field_newsroom_type_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_newsroom_type_value']['value'] = array(
    'default' => 'default',
  );

  /* Display: Month */
  $handler = $view->new_display('page', 'Month', 'month');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fullcalendar';
  $handler->display->display_options['style_options']['firstDay'] = '1';
  $handler->display->display_options['style_options']['advanced'] = TRUE;
  $handler->display->display_options['style_options']['timeformatMonth'] = '';
  $handler->display->display_options['style_options']['timeformatWeek'] = '';
  $handler->display->display_options['style_options']['timeformatDay'] = '';
  $handler->display->display_options['style_options']['theme'] = FALSE;
  $handler->display->display_options['style_options']['sameWindow'] = TRUE;
  $handler->display->display_options['style_options']['fields']['title_field'] = 'field_newsroom_item_short_title';
  $handler->display->display_options['style_options']['fields']['date_field'] = array(
    'field_newsroom_item_date' => 'field_newsroom_item_date',
  );
  $handler->display->display_options['style_options']['fields']['title'] = TRUE;
  $handler->display->display_options['style_options']['fields']['date'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['vocabularies'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['transform'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '0';
  $handler->display->display_options['path'] = 'newsroom/calendar';
  $handler->display->display_options['menu']['title'] = 'Events';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Events';
  $handler->display->display_options['tab_options']['weight'] = '2';
  $handler->display->display_options['tab_options']['name'] = 'main-menu';

  /* Display: Calendar block */
  $handler = $view->new_display('block', 'Calendar block', 'calendar_block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Calendar';
  $handler->display->display_options['display_description'] = 'Calendar to be displayed mainly in left or right sidebars';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fullcalendar';
  $handler->display->display_options['style_options']['firstDay'] = '1';
  $handler->display->display_options['style_options']['weekMode'] = 'liquid';
  $handler->display->display_options['style_options']['left'] = '';
  $handler->display->display_options['style_options']['center'] = 'prev title next';
  $handler->display->display_options['style_options']['right'] = 'month';
  $handler->display->display_options['style_options']['advanced'] = TRUE;
  $handler->display->display_options['style_options']['titleformatDay'] = 'MMM d, yyyy';
  $handler->display->display_options['style_options']['editable'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['block_description'] = 'Calendar block';
  $translatables['newsroom_calendar'] = array(
    t('Master'),
    t('<none>'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<h2>Consult planned events</h2>'),
    t('term from field_newsroom_item_type'),
    t('[path]'),
    t('[field_newsroom_item_main_link]'),
    t('[title]'),
    t('All taxonomy terms'),
    t('Body'),
    t('Month'),
    t('All'),
    t('Calendar block'),
    t('Calendar'),
    t('Calendar to be displayed mainly in left or right sidebars'),
  );
  $export['newsroom_calendar'] = $view;

  $view = new view();
  $view->name = 'newsroom_calendar_navigation';
  $view->description = '';
  $view->tag = 'newsroom';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Newsroom Calendar Navigation';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '[nothing]';
  $handler->display->display_options['css_class'] = 'nav-panel block-menu-block';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'tree';
  $handler->display->display_options['style_options']['main_field'] = 'tid';
  $handler->display->display_options['style_options']['parent_field'] = 'tid_1';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Taxonomy term: Parent term */
  $handler->display->display_options['relationships']['parent']['id'] = 'parent';
  $handler->display->display_options['relationships']['parent']['table'] = 'taxonomy_term_hierarchy';
  $handler->display->display_options['relationships']['parent']['field'] = 'parent';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['relationship'] = 'parent';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid_1']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'newsroom/[name]/!2';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['null']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['fail'] = 'ignore';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['null_1']['default_argument_options']['index'] = '2';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null_1']['validate']['fail'] = 'ignore';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'collection');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'nav nav-pills';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Calendar';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'newsroom/calendar';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['relationship'] = 'parent';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid_1']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'newsroom/calendar/[name]/';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
  );
  /* Filter criterion: Taxonomy term: Listing behavior (field_newsroom_type) */
  $handler->display->display_options['filters']['field_newsroom_type_value']['id'] = 'field_newsroom_type_value';
  $handler->display->display_options['filters']['field_newsroom_type_value']['table'] = 'field_data_field_newsroom_type';
  $handler->display->display_options['filters']['field_newsroom_type_value']['field'] = 'field_newsroom_type_value';
  $handler->display->display_options['filters']['field_newsroom_type_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_newsroom_type_value']['value'] = array(
    'default' => 'default',
  );
  $translatables['newsroom_calendar_navigation'] = array(
    t('Master'),
    t('[nothing]'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Parent'),
    t('.'),
    t('All'),
    t('Block'),
    t('Calendar'),
  );
  $export['newsroom_calendar_navigation'] = $view;

  $view = new view();
  $view->name = 'newsroom_navigation';
  $view->description = '';
  $view->tag = 'newsroom';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Newsroom Navigation';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '[nothing]';
  $handler->display->display_options['css_class'] = 'nav-panel block-menu-block';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'tree';
  $handler->display->display_options['style_options']['main_field'] = 'tid';
  $handler->display->display_options['style_options']['parent_field'] = 'tid_1';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Taxonomy term: Parent term */
  $handler->display->display_options['relationships']['parent']['id'] = 'parent';
  $handler->display->display_options['relationships']['parent']['table'] = 'taxonomy_term_hierarchy';
  $handler->display->display_options['relationships']['parent']['field'] = 'parent';
  /* Relationship: Taxonomy term: Content using Newsroom Item Type */
  $handler->display->display_options['relationships']['reverse_field_newsroom_item_type_node']['id'] = 'reverse_field_newsroom_item_type_node';
  $handler->display->display_options['relationships']['reverse_field_newsroom_item_type_node']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['reverse_field_newsroom_item_type_node']['field'] = 'reverse_field_newsroom_item_type_node';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['relationship'] = 'parent';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid_1']['separator'] = '';
  /* Field: Entity translation: Name: translated */
  $handler->display->display_options['fields']['name_field_et']['id'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et']['table'] = 'field_data_name_field';
  $handler->display->display_options['fields']['name_field_et']['field'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et']['label'] = '';
  $handler->display->display_options['fields']['name_field_et']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name_field_et']['element_type'] = '0';
  $handler->display->display_options['fields']['name_field_et']['element_label_type'] = '0';
  $handler->display->display_options['fields']['name_field_et']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name_field_et']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name_field_et']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['name_field_et']['type'] = 'text_plain';
  /* Field: Filtered name */
  $handler->display->display_options['fields']['name_field_et_1']['id'] = 'name_field_et_1';
  $handler->display->display_options['fields']['name_field_et_1']['table'] = 'field_data_name_field';
  $handler->display->display_options['fields']['name_field_et_1']['field'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et_1']['ui_name'] = 'Filtered name';
  $handler->display->display_options['fields']['name_field_et_1']['label'] = '';
  $handler->display->display_options['fields']['name_field_et_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name_field_et_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name_field_et_1']['type'] = 'newsroom_pathauto';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['text'] = '[name_field_et]';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'newsroom/[name_field_et_1]/!2';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['null']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['fail'] = 'ignore';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['null_1']['default_argument_options']['index'] = '2';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null_1']['validate']['fail'] = 'ignore';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'type');

  /* Display: Collection Block */
  $handler = $view->new_display('block', 'Collection Block', 'collection');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'nav nav-pills';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['relationship'] = 'parent';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid_1']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'newsroom/[name]/!2';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  /* Filter criterion: Taxonomy term: Newsroom Category Domain (field_newsroom_category_domain) */
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['id'] = 'field_newsroom_category_domain_value';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['table'] = 'field_data_field_newsroom_category_domain';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['field'] = 'field_newsroom_category_domain_value';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['value'] = 'Collection';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'type_for_calendar');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['relationship'] = 'parent';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid_1']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'newsroom/[name]';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'collection_for_calendar');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'nav nav-pills';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['relationship'] = 'parent';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid_1']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'newsroom/[name]';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'newsroom';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  /* Filter criterion: Taxonomy term: Newsroom Category Domain (field_newsroom_category_domain) */
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['id'] = 'field_newsroom_category_domain_value';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['table'] = 'field_data_field_newsroom_category_domain';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['field'] = 'field_newsroom_category_domain_value';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['value'] = 'Collection';

  $export['newsroom_navigation'] = $view;

  $view = new view();
  $view->name = 'newsroom_page_content';
  $view->description = '';
  $view->tag = 'newsroom';
  $view->base_table = 'node';
  $view->human_name = 'Newsroom Page Content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '%1';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'clearfix term-[field_newsroom_item_type_1]';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_newsroom_item_type' => 'field_newsroom_item_type',
    'title' => 'title',
    'field_newsroom_item_date' => 'field_newsroom_item_date',
  );
  /* Relationship: Content: Newsroom Item Type (field_newsroom_item_type) */
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['id'] = 'field_newsroom_item_type_tid';
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['table'] = 'field_data_field_newsroom_item_type';
  $handler->display->display_options['relationships']['field_newsroom_item_type_tid']['field'] = 'field_newsroom_item_type_tid';
  /* Field: Content: Newsroom Item Type */
  $handler->display->display_options['fields']['field_newsroom_item_type']['id'] = 'field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['table'] = 'field_data_field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['field'] = 'field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['alter']['text'] = '[field_newsroom_item_type]:';
  $handler->display->display_options['fields']['field_newsroom_item_type']['element_type'] = '0';
  $handler->display->display_options['fields']['field_newsroom_item_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_type'] = '0';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Main Link */
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['id'] = 'field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['table'] = 'field_data_field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['field'] = 'field_newsroom_item_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['empty'] = '[path]';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['type'] = 'newsroom_main_link';
  $handler->display->display_options['fields']['field_newsroom_item_main_link']['settings'] = array(
    'display_type' => 'default',
  );
  /* Field: Entity translation: Title: translated */
  $handler->display->display_options['fields']['title_field_et']['id'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field_et']['field'] = 'title_field_et';
  $handler->display->display_options['fields']['title_field_et']['label'] = '';
  $handler->display->display_options['fields']['title_field_et']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_field_et']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title_field_et']['alter']['path'] = '[field_newsroom_item_main_link]';
  $handler->display->display_options['fields']['title_field_et']['element_label_colon'] = FALSE;
  /* Field: Content: Short Title */
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['id'] = 'field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['table'] = 'field_data_field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['field'] = 'field_newsroom_item_short_title';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['alter']['path'] = '[field_newsroom_item_main_link]';
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_short_title']['empty'] = '[title_field_et]';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_newsroom_item_date']['id'] = 'field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['field'] = 'field_newsroom_item_date';
  $handler->display->display_options['fields']['field_newsroom_item_date']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_date']['alter']['text'] = 'deadline: [field_newsroom_item_date]';
  $handler->display->display_options['fields']['field_newsroom_item_date']['element_type'] = '0';
  $handler->display->display_options['fields']['field_newsroom_item_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_date']['settings'] = array(
    'format_type' => 'date_only',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Venue */
  $handler->display->display_options['fields']['field_newsroom_item_venue']['id'] = 'field_newsroom_item_venue';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['table'] = 'field_data_field_newsroom_item_venue';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['field'] = 'field_newsroom_item_venue';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_venue']['alter']['text'] = '[field_newsroom_item_venue], ';
  $handler->display->display_options['fields']['field_newsroom_item_venue']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_venue']['hide_empty'] = TRUE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'date_only';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['vocabularies'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '1';
  $handler->display->display_options['arguments']['term_node_tid_depth']['break_phrase'] = TRUE;
  /* Contextual filter: Content: Newsroom: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['id'] = 'newsroom_term_node_tid_depth';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['field'] = 'newsroom_term_node_tid_depth';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['validate_options']['vocabularies'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['depth'] = '0';
  $handler->display->display_options['arguments']['newsroom_term_node_tid_depth']['break_phrase'] = TRUE;
  /* Contextual filter: Content: Highlighted Newsroom Topics (field_highlighted_newsroom_topic) */
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['id'] = 'field_highlighted_newsroom_topic_tid';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['table'] = 'field_data_field_highlighted_newsroom_topic';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['field'] = 'field_highlighted_newsroom_topic_tid';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_highlighted_newsroom_topic_tid']['validate_options']['vocabularies'] = array(
    'newsroom_topic' => 'newsroom_topic',
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  /* Filter criterion: Content: Sticky */
  $handler->display->display_options['filters']['sticky']['id'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['table'] = 'node';
  $handler->display->display_options['filters']['sticky']['field'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['value'] = '1';

  /* Display: Newsroom */
  $handler = $view->new_display('block', 'Newsroom', 'default_newsroom');
  $handler->display->display_options['display_description'] = 'Newsroom';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';

  /* Display: Consultation / Fundin Opportunities */
  $handler = $view->new_display('block', 'Consultation / Fundin Opportunities', 'consultation_funding');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['default_date'] = 'now';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['id'] = 'field_newsroom_item_date_value2_1';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['group'] = 2;

  /* Display: Events */
  $handler = $view->new_display('block', 'Events', 'events');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Date -  start date (field_newsroom_item_date) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['id'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['field'] = 'field_newsroom_item_date_value';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value']['order'] = 'DESC';
  /* Sort criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['default_date'] = 'now';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['id'] = 'field_newsroom_item_date_value2_1';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2_1']['group'] = 2;

  /* Display: Agenda */
  $handler = $view->new_display('block', 'Agenda', 'agenda');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_newsroom_item_date',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'clearfix term-[field_newsroom_item_type_1]';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_newsroom_item_type' => 'field_newsroom_item_type',
    'title' => 'title',
    'field_newsroom_item_date' => 'field_newsroom_item_date',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['sorts']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'newsroom_item' => 'newsroom_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date - end date (field_newsroom_item_date:value2) */
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['id'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['table'] = 'field_data_field_newsroom_item_date';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['field'] = 'field_newsroom_item_date_value2';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_newsroom_item_date_value2']['default_date'] = 'now';

  $translatables['newsroom_page_content'] = array(
    t('Master'),
    t('%1'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('term from field_newsroom_item_type'),
    t('[field_newsroom_item_type]:'),
    t('[path]'),
    t('[field_newsroom_item_main_link]'),
    t('[title]'),
    t('deadline: [field_newsroom_item_date]'),
    t('[field_newsroom_item_venue],'),
    t('Read more'),
    t('<p>[field_shared_teaser] [view_node]</p>'),
    t('[field_newsroom_item_type_1-tid]'),
    t('All'),
    t('Newsroom'),
    t('Consultation / Fundin Opportunities'),
    t('<span class="date_prefix">Deadline:</span> [field_newsroom_item_date]'),
    t('Events'),
    t('Agenda'),
  );
  $export['newsroom_page_content'] = $view;

  $view = new view();
  $view->name = 'newsroom_related_content';
  $view->description = '';
  $view->tag = 'newsroom';
  $view->base_table = 'node';
  $view->human_name = 'Newsroom related content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Related content';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Related content */
  $handler->display->display_options['fields']['field_related_content']['id'] = 'field_related_content';
  $handler->display->display_options['fields']['field_related_content']['table'] = 'field_data_field_related_content';
  $handler->display->display_options['fields']['field_related_content']['field'] = 'field_related_content';
  $handler->display->display_options['fields']['field_related_content']['label'] = '';
  $handler->display->display_options['fields']['field_related_content']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_related_content']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_related_content']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_related_content']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_related_content']['multi_type'] = 'ul';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'newsroom_item' => 'newsroom_item',
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
    'newsroom_item' => 'newsroom_item',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_related_content_node']['id'] = 'reverse_field_related_content_node';
  $handler->display->display_options['relationships']['reverse_field_related_content_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_related_content_node']['field'] = 'reverse_field_related_content_node';
  $handler->display->display_options['relationships']['reverse_field_related_content_node']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_related_content_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['displays'] = array(
    'block' => 'block',
    'default' => 0,
  );
  $translatables['newsroom_related_content'] = array(
    t('Master'),
    t('Related content'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('All'),
    t('Block'),
    t('Attachment'),
    t('Content referencing Content from field_related_content'),
  );
  $export['newsroom_related_content'] = $view;

  $view = new view();
  $view->name = 'newsroom_term_selection';
  $view->description = '';
  $view->tag = 'newsroom';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Newsroom term selection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Newsroom Category Domain */
  $handler->display->display_options['fields']['field_newsroom_category_domain']['id'] = 'field_newsroom_category_domain';
  $handler->display->display_options['fields']['field_newsroom_category_domain']['table'] = 'field_data_field_newsroom_category_domain';
  $handler->display->display_options['fields']['field_newsroom_category_domain']['field'] = 'field_newsroom_category_domain';
  $handler->display->display_options['fields']['field_newsroom_category_domain']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_category_domain']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['text'] = '%5B[field_newsroom_category_domain]%5D [name]';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Sort criterion: Taxonomy term: Newsroom Category Domain (field_newsroom_category_domain) */
  $handler->display->display_options['sorts']['field_newsroom_category_domain_value']['id'] = 'field_newsroom_category_domain_value';
  $handler->display->display_options['sorts']['field_newsroom_category_domain_value']['table'] = 'field_data_field_newsroom_category_domain';
  $handler->display->display_options['sorts']['field_newsroom_category_domain_value']['field'] = 'field_newsroom_category_domain_value';
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );

  /* Display: Topics */
  $handler = $view->new_display('entityreference', 'Topics', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_newsroom_category_domain' => 'field_newsroom_category_domain',
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_newsroom_category_domain' => 'field_newsroom_category_domain',
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Newsletters */
  $handler = $view->new_display('entityreference', 'Newsletters', 'entityreference_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['text'] = '%5B[field_newsroom_category_domain]%5D [name]';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service type (field_service_type) */
  $handler->display->display_options['filters']['field_service_type_value']['id'] = 'field_service_type_value';
  $handler->display->display_options['filters']['field_service_type_value']['table'] = 'field_data_field_service_type';
  $handler->display->display_options['filters']['field_service_type_value']['field'] = 'field_service_type_value';
  $handler->display->display_options['filters']['field_service_type_value']['value'] = 'Newsletter';
  /* Filter criterion: Taxonomy term: Service active (field_service_active) */
  $handler->display->display_options['filters']['field_service_active_value']['id'] = 'field_service_active_value';
  $handler->display->display_options['filters']['field_service_active_value']['table'] = 'field_data_field_service_active';
  $handler->display->display_options['filters']['field_service_active_value']['field'] = 'field_service_active_value';
  $handler->display->display_options['filters']['field_service_active_value']['value'] = 'Active';

  /* Display: Collections */
  $handler = $view->new_display('entityreference', 'Collections', 'entityreference_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_newsroom_category_domain' => 'field_newsroom_category_domain',
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_newsroom_category_domain' => 'field_newsroom_category_domain',
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_topic' => 'newsroom_topic',
  );
  /* Filter criterion: Taxonomy term: Newsroom Category Domain (field_newsroom_category_domain) */
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['id'] = 'field_newsroom_category_domain_value';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['table'] = 'field_data_field_newsroom_category_domain';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['field'] = 'field_newsroom_category_domain_value';
  $handler->display->display_options['filters']['field_newsroom_category_domain_value']['value'] = 'Collection';
  $translatables['newsroom_term_selection'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('%5B[field_newsroom_category_domain]%5D [name]'),
    t('.'),
    t('Topics'),
    t('Newsletters'),
    t('Collections'),
  );
  $export['newsroom_term_selection'] = $view;

  $view = new view();
  $view->name = 'newsroom_type_featured_item';
  $view->description = '';
  $view->tag = 'newsroom';
  $view->base_table = 'node';
  $view->human_name = 'Newsroom Type Featured Item';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Newsroom Type Featured Item';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_featured_item_taxonomy_term']['id'] = 'reverse_field_featured_item_taxonomy_term';
  $handler->display->display_options['relationships']['reverse_field_featured_item_taxonomy_term']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_featured_item_taxonomy_term']['field'] = 'reverse_field_featured_item_taxonomy_term';
  $handler->display->display_options['relationships']['reverse_field_featured_item_taxonomy_term']['required'] = TRUE;
  /* Field: Content: default instance */
  $handler->display->display_options['fields']['field_newsroom_item_type']['id'] = 'field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['table'] = 'field_data_field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['field'] = 'field_newsroom_item_type';
  $handler->display->display_options['fields']['field_newsroom_item_type']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_item_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['alter']['path'] = 'newsroom/!1/all';
  $handler->display->display_options['fields']['field_newsroom_item_type']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_item_type']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: default instance */
  $handler->display->display_options['fields']['field_illustrative_image']['id'] = 'field_illustrative_image';
  $handler->display->display_options['fields']['field_illustrative_image']['table'] = 'field_data_field_illustrative_image';
  $handler->display->display_options['fields']['field_illustrative_image']['field'] = 'field_illustrative_image';
  $handler->display->display_options['fields']['field_illustrative_image']['label'] = '';
  $handler->display->display_options['fields']['field_illustrative_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_illustrative_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_illustrative_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_illustrative_image']['settings'] = array(
    'image_style' => 'large',
    'image_link' => 'content',
  );
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'date_only';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'date_only';
  /* Field: Teaser */
  $handler->display->display_options['fields']['field_teaser']['id'] = 'field_teaser';
  $handler->display->display_options['fields']['field_teaser']['table'] = 'field_data_field_teaser';
  $handler->display->display_options['fields']['field_teaser']['field'] = 'field_teaser';
  $handler->display->display_options['fields']['field_teaser']['ui_name'] = 'Teaser';
  $handler->display->display_options['fields']['field_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_teaser']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_teaser']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="newsroom-featured-item">
    <div class="newsroom-type">[field_newsroom_item_type]</div>
    <div class="newsroom-title">[title]</div>
    <div class="newsroom-image">[field_illustrative_image] </div>
    <div class="newsroom-date">[created]</div>
    <div class="newsroom-teaser">[field_teaser]</div>
    </div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Taxonomy term: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['relationship'] = 'reverse_field_featured_item_taxonomy_term';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'newsroom_item_type' => 'newsroom_item_type',
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['tid']['validate_options']['transform'] = TRUE;
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
    'newsroom_item' => 'newsroom_item',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');


  $export['newsroom_type_featured_item'] = $view;

  return $export;
}