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
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '300';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '300';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  /* Filter criterion: Taxonomy term: Service type (field_newsroom_service_type) */
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['id'] = 'field_newsroom_service_type_value';
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['table'] = 'field_data_field_newsroom_service_type';
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['field'] = 'field_newsroom_service_type_value';
  $handler->display->display_options['filters']['field_newsroom_service_type_value']['value'] = 'Newsletter';
  /* Filter criterion: Taxonomy term: Service active (field_newsroom_service_active) */
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['id'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['table'] = 'field_data_field_newsroom_service_active';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['field'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['value'] = 'Active';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['newsletter_subscription'] = $view;

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
  $handler->display->display_options['title'] = 'Newsroom';
  $handler->display->display_options['css_class'] = 'nav-panel block-menu-block';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
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
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
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
  $handler = $view->new_display('block', 'Block', 'block');
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
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Agenda';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'newsroom-agenda/schedule/all/all';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['fields']['tid_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid_1']['field'] = 'tid';
  $handler->display->display_options['fields']['tid_1']['label'] = '';
  $handler->display->display_options['fields']['tid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid_1']['separator'] = '';
  /* Field: Entity translation: Name: translated */
  $handler->display->display_options['fields']['name_field_et']['id'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et']['table'] = 'field_data_name_field';
  $handler->display->display_options['fields']['name_field_et']['field'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et']['label'] = 'URL';
  $handler->display->display_options['fields']['name_field_et']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name_field_et']['type'] = 'newsroom_pathauto';
  /* Field: Entity translation: Name: translated */
  $handler->display->display_options['fields']['name_field_et_1']['id'] = 'name_field_et_1';
  $handler->display->display_options['fields']['name_field_et_1']['table'] = 'field_data_name_field';
  $handler->display->display_options['fields']['name_field_et_1']['field'] = 'name_field_et';
  $handler->display->display_options['fields']['name_field_et_1']['label'] = '';
  $handler->display->display_options['fields']['name_field_et_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name_field_et_1']['alter']['path'] = 'newsroom-agenda/schedule/[name_field_et]/all/';
  $handler->display->display_options['fields']['name_field_et_1']['element_label_colon'] = FALSE;
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
  /* Filter criterion: Taxonomy term: Newsroom Type ID (field_newsroom_type_id) */
  $handler->display->display_options['filters']['field_newsroom_type_id_value']['id'] = 'field_newsroom_type_id_value';
  $handler->display->display_options['filters']['field_newsroom_type_id_value']['table'] = 'field_data_field_newsroom_type_id';
  $handler->display->display_options['filters']['field_newsroom_type_id_value']['field'] = 'field_newsroom_type_id_value';
  $handler->display->display_options['filters']['field_newsroom_type_id_value']['operator'] = '!=';
  $handler->display->display_options['filters']['field_newsroom_type_id_value']['value'] = '300';
  $export['newsroom_calendar_navigation'] = $view;

  $view = new view();
  $view->name = 'newsroom_services';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Newsroom services';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Central Newsletters';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '86400';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '86400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Image */
  $handler->display->display_options['fields']['field_newsroom_service_image']['id'] = 'field_newsroom_service_image';
  $handler->display->display_options['fields']['field_newsroom_service_image']['table'] = 'field_data_field_newsroom_service_image';
  $handler->display->display_options['fields']['field_newsroom_service_image']['field'] = 'field_newsroom_service_image';
  $handler->display->display_options['fields']['field_newsroom_service_image']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_service_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_newsroom_service_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_newsroom_service_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Newsroom Service ID */
  $handler->display->display_options['fields']['field_newsroom_service_id']['id'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['table'] = 'field_data_field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['field'] = 'field_newsroom_service_id';
  $handler->display->display_options['fields']['field_newsroom_service_id']['label'] = '';
  $handler->display->display_options['fields']['field_newsroom_service_id']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service active (field_newsroom_service_active) */
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['id'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['table'] = 'field_data_field_newsroom_service_active';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['field'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['value'] = 'Active';
  /* Filter criterion: Taxonomy term: Basic mailing (field_newsroom_basic_mailing) */
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['id'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['table'] = 'field_data_field_newsroom_basic_mailing';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['field'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['value'] = array(
    1 => '1',
  );

  /* Display: Central newsletters */
  $handler = $view->new_display('block', 'Central newsletters', 'basic');
  $handler->display->display_options['block_caching'] = '8';

  /* Display: Basic newsletters */
  $handler = $view->new_display('block', 'Basic newsletters', 'central');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Other newsletters';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'newsroom_service' => 'newsroom_service',
  );
  /* Filter criterion: Taxonomy term: Service active (field_newsroom_service_active) */
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['id'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['table'] = 'field_data_field_newsroom_service_active';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['field'] = 'field_newsroom_service_active_value';
  $handler->display->display_options['filters']['field_newsroom_service_active_value']['value'] = 'Active';
  /* Filter criterion: Taxonomy term: Basic mailing (field_newsroom_basic_mailing) */
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['id'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['table'] = 'field_data_field_newsroom_basic_mailing';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['field'] = 'field_newsroom_basic_mailing_value';
  $handler->display->display_options['filters']['field_newsroom_basic_mailing_value']['value'] = array(
    0 => '0',
  );
  $export['newsroom_services'] = $view;

  return $export;
}
