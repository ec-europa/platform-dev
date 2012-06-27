<?php
/**
 * @file
 * eaq_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function eaq_feature_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'ask_a_question';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ask a Question';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Overview Questions';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'field_creation_timestamp' => 'field_creation_timestamp',
    'field_origin_country' => 'field_origin_country',
    'field_related_country' => 'field_related_country',
    'field_language' => 'field_language',
    'field_theme' => 'field_theme',
    'field_assigned_user_uid' => 'field_assigned_user_uid',
    'field_handled' => 'field_handled',
    'nothing_2' => 'nothing_2',
    'nothing' => 'nothing_2',
    'nothing_1' => 'nothing_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_creation_timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_origin_country' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_related_country' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_language' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_theme' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_assigned_user_uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_handled' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_2' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Creation timestamp */
  $handler->display->display_options['fields']['field_creation_timestamp']['id'] = 'field_creation_timestamp';
  $handler->display->display_options['fields']['field_creation_timestamp']['table'] = 'field_data_field_creation_timestamp';
  $handler->display->display_options['fields']['field_creation_timestamp']['field'] = 'field_creation_timestamp';
  $handler->display->display_options['fields']['field_creation_timestamp']['label'] = 'Date';
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_creation_timestamp']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_creation_timestamp']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_creation_timestamp']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_creation_timestamp']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_creation_timestamp']['field_api_classes'] = 0;
  /* Field: Content: Origin Country */
  $handler->display->display_options['fields']['field_origin_country']['id'] = 'field_origin_country';
  $handler->display->display_options['fields']['field_origin_country']['table'] = 'field_data_field_origin_country';
  $handler->display->display_options['fields']['field_origin_country']['field'] = 'field_origin_country';
  $handler->display->display_options['fields']['field_origin_country']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_origin_country']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_origin_country']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_origin_country']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_origin_country']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_origin_country']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_origin_country']['field_api_classes'] = 0;
  /* Field: Content: Related Country */
  $handler->display->display_options['fields']['field_related_country']['id'] = 'field_related_country';
  $handler->display->display_options['fields']['field_related_country']['table'] = 'field_data_field_related_country';
  $handler->display->display_options['fields']['field_related_country']['field'] = 'field_related_country';
  $handler->display->display_options['fields']['field_related_country']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_related_country']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_related_country']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_related_country']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_related_country']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_related_country']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_related_country']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_related_country']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_related_country']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_related_country']['field_api_classes'] = 0;
  /* Field: Content: Language */
  $handler->display->display_options['fields']['field_language']['id'] = 'field_language';
  $handler->display->display_options['fields']['field_language']['table'] = 'field_data_field_language';
  $handler->display->display_options['fields']['field_language']['field'] = 'field_language';
  $handler->display->display_options['fields']['field_language']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_language']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_language']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_language']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_language']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_language']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_language']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_language']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_language']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_language']['field_api_classes'] = 0;
  /* Field: Content: Theme */
  $handler->display->display_options['fields']['field_theme']['id'] = 'field_theme';
  $handler->display->display_options['fields']['field_theme']['table'] = 'field_data_field_theme';
  $handler->display->display_options['fields']['field_theme']['field'] = 'field_theme';
  $handler->display->display_options['fields']['field_theme']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_theme']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_theme']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_theme']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_theme']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_theme']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_theme']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_theme']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_theme']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_theme']['field_api_classes'] = 0;
  /* Field: Content: Assigned User_uid */
  $handler->display->display_options['fields']['field_assigned_user_uid']['id'] = 'field_assigned_user_uid';
  $handler->display->display_options['fields']['field_assigned_user_uid']['table'] = 'field_data_field_assigned_user_uid';
  $handler->display->display_options['fields']['field_assigned_user_uid']['field'] = 'field_assigned_user_uid';
  $handler->display->display_options['fields']['field_assigned_user_uid']['label'] = 'Assignee';
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_assigned_user_uid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_assigned_user_uid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_assigned_user_uid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_assigned_user_uid']['type'] = 'text_user_name';
  $handler->display->display_options['fields']['field_assigned_user_uid']['field_api_classes'] = 0;
  /* Field: Content: Handled */
  $handler->display->display_options['fields']['field_handled']['id'] = 'field_handled';
  $handler->display->display_options['fields']['field_handled']['table'] = 'field_data_field_handled';
  $handler->display->display_options['fields']['field_handled']['field'] = 'field_handled';
  $handler->display->display_options['fields']['field_handled']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_handled']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_handled']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_handled']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_handled']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_handled']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_handled']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_handled']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_handled']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_handled']['field_api_classes'] = 0;
  /* Field: Content: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'node';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = 1;
  /* Sort criterion: Content: Creation timestamp (field_creation_timestamp) */
  $handler->display->display_options['sorts']['field_creation_timestamp_value']['id'] = 'field_creation_timestamp_value';
  $handler->display->display_options['sorts']['field_creation_timestamp_value']['table'] = 'field_data_field_creation_timestamp';
  $handler->display->display_options['sorts']['field_creation_timestamp_value']['field'] = 'field_creation_timestamp_value';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ask_a_question' => 'ask_a_question',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Theme (field_theme) */
  $handler->display->display_options['filters']['field_theme_value']['id'] = 'field_theme_value';
  $handler->display->display_options['filters']['field_theme_value']['table'] = 'field_data_field_theme';
  $handler->display->display_options['filters']['field_theme_value']['field'] = 'field_theme_value';
  $handler->display->display_options['filters']['field_theme_value']['group'] = 1;
  $handler->display->display_options['filters']['field_theme_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_theme_value']['expose']['operator_id'] = 'field_theme_value_op';
  $handler->display->display_options['filters']['field_theme_value']['expose']['label'] = 'Theme';
  $handler->display->display_options['filters']['field_theme_value']['expose']['operator'] = 'field_theme_value_op';
  $handler->display->display_options['filters']['field_theme_value']['expose']['identifier'] = 'theme';
  $handler->display->display_options['filters']['field_theme_value']['expose']['reduce'] = 0;
  /* Filter criterion: Content: Origin Country (field_origin_country) */
  $handler->display->display_options['filters']['field_origin_country_value']['id'] = 'field_origin_country_value';
  $handler->display->display_options['filters']['field_origin_country_value']['table'] = 'field_data_field_origin_country';
  $handler->display->display_options['filters']['field_origin_country_value']['field'] = 'field_origin_country_value';
  $handler->display->display_options['filters']['field_origin_country_value']['group'] = 1;
  $handler->display->display_options['filters']['field_origin_country_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_origin_country_value']['expose']['operator_id'] = 'field_origin_country_value_op';
  $handler->display->display_options['filters']['field_origin_country_value']['expose']['label'] = 'Origin Country';
  $handler->display->display_options['filters']['field_origin_country_value']['expose']['operator'] = 'field_origin_country_value_op';
  $handler->display->display_options['filters']['field_origin_country_value']['expose']['identifier'] = 'origin_country';
  $handler->display->display_options['filters']['field_origin_country_value']['expose']['reduce'] = 0;
  /* Filter criterion: Content: Related Country (field_related_country) */
  $handler->display->display_options['filters']['field_related_country_value']['id'] = 'field_related_country_value';
  $handler->display->display_options['filters']['field_related_country_value']['table'] = 'field_data_field_related_country';
  $handler->display->display_options['filters']['field_related_country_value']['field'] = 'field_related_country_value';
  $handler->display->display_options['filters']['field_related_country_value']['group'] = 1;
  $handler->display->display_options['filters']['field_related_country_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_related_country_value']['expose']['operator_id'] = 'field_related_country_value_op';
  $handler->display->display_options['filters']['field_related_country_value']['expose']['label'] = 'Related Country';
  $handler->display->display_options['filters']['field_related_country_value']['expose']['operator'] = 'field_related_country_value_op';
  $handler->display->display_options['filters']['field_related_country_value']['expose']['identifier'] = 'related_country';
  $handler->display->display_options['filters']['field_related_country_value']['expose']['reduce'] = 0;
  /* Filter criterion: Content: Language (field_language) */
  $handler->display->display_options['filters']['field_language_value']['id'] = 'field_language_value';
  $handler->display->display_options['filters']['field_language_value']['table'] = 'field_data_field_language';
  $handler->display->display_options['filters']['field_language_value']['field'] = 'field_language_value';
  $handler->display->display_options['filters']['field_language_value']['group'] = 1;
  $handler->display->display_options['filters']['field_language_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_language_value']['expose']['operator_id'] = 'field_language_value_op';
  $handler->display->display_options['filters']['field_language_value']['expose']['label'] = 'Language';
  $handler->display->display_options['filters']['field_language_value']['expose']['operator'] = 'field_language_value_op';
  $handler->display->display_options['filters']['field_language_value']['expose']['identifier'] = 'language';
  $handler->display->display_options['filters']['field_language_value']['expose']['reduce'] = 0;
  /* Filter criterion: Content: Handled (field_handled) */
  $handler->display->display_options['filters']['field_handled_value']['id'] = 'field_handled_value';
  $handler->display->display_options['filters']['field_handled_value']['table'] = 'field_data_field_handled';
  $handler->display->display_options['filters']['field_handled_value']['field'] = 'field_handled_value';
  $handler->display->display_options['filters']['field_handled_value']['value'] = array(
    0 => '0',
  );
  $handler->display->display_options['filters']['field_handled_value']['group'] = 1;
  $handler->display->display_options['filters']['field_handled_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_handled_value']['expose']['operator_id'] = 'field_handled_value_op';
  $handler->display->display_options['filters']['field_handled_value']['expose']['label'] = 'Handled';
  $handler->display->display_options['filters']['field_handled_value']['expose']['operator'] = 'field_handled_value_op';
  $handler->display->display_options['filters']['field_handled_value']['expose']['identifier'] = 'handled';
  $handler->display->display_options['filters']['field_handled_value']['expose']['reduce'] = 0;
  /* Filter criterion: Content: Assigned User_uid (field_assigned_user_uid) */
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['id'] = 'field_assigned_user_uid_value';
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['table'] = 'field_data_field_assigned_user_uid';
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['field'] = 'field_assigned_user_uid_value';
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['group'] = 1;
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['expose']['operator_id'] = 'field_assigned_user_uid_value_op';
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['expose']['label'] = 'Assignee';
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['expose']['operator'] = 'field_assigned_user_uid_value_op';
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['expose']['identifier'] = 'assignee';
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['expose']['required'] = 0;
  $handler->display->display_options['filters']['field_assigned_user_uid_value']['expose']['multiple'] = FALSE;
  $translatables['ask_a_question'] = array(
    t('Master'),
    t('Overview Questions'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Date'),
    t('Origin Country'),
    t('Related Country'),
    t('Language'),
    t('Theme'),
    t('Assignee'),
    t('Handled'),
    t('Operations'),
  );
  $export['ask_a_question'] = $view;

  return $export;
}
