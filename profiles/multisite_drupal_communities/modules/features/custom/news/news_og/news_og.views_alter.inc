<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function news_og_views_default_views_alter(&$views) {
  if (array_key_exists('news', $views)) {
    $view=$views['news'];

    /* Display: Defaults */ 
    $handler = $view->display['default']->handler;  
    /* Relationship: OG membership: OG membership from Node */
    $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
    $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
    
    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'og_context';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
    );

    $handler = $view->display['page']->handler;
    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
    );  
    $handler->display->display_options['defaults']['filters'] = FALSE; 
  



    /* Display: news_public */
    $handler = $view->new_display('page', 'news_public', 'page_1');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'grid';
    $handler->display->display_options['style_options']['columns'] = '3';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['element_type'] = 'h3';
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    /* Field: Content: Post date */
    $handler->display->display_options['fields']['created']['id'] = 'created';
    $handler->display->display_options['fields']['created']['table'] = 'node';
    $handler->display->display_options['fields']['created']['field'] = 'created';
    $handler->display->display_options['fields']['created']['label'] = '';
    $handler->display->display_options['fields']['created']['alter']['text'] = '<small>[created]</small>';
    $handler->display->display_options['fields']['created']['element_class'] = 'meta';
    $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['created']['date_format'] = 'short';
    /* Field: Content: Body */
    $handler->display->display_options['fields']['body']['id'] = 'body';
    $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
    $handler->display->display_options['fields']['body']['field'] = 'body';
    $handler->display->display_options['fields']['body']['label'] = '';
    $handler->display->display_options['fields']['body']['alter']['max_length'] = '600';
    $handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
    $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['body']['element_wrapper_class'] = 'fieldset clearfix';
    $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
    $handler->display->display_options['fields']['body']['settings'] = array(
      'trim_length' => '600',
    );
    /* Field: Content: link */
    $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
    $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
    $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
    $handler->display->display_options['fields']['field_link']['label'] = 'Related link';
    $handler->display->display_options['fields']['field_link']['element_type'] = '0';
    $handler->display->display_options['fields']['field_link']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['field_link']['hide_empty'] = TRUE;
    $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
    $handler->display->display_options['fields']['field_link']['delta_offset'] = '0';
    /* Field: Content: Groups audience */
    $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
    $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
    $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
    $handler->display->display_options['fields']['og_group_ref']['label'] = 'Group';
    $handler->display->display_options['fields']['og_group_ref']['hide_empty'] = TRUE;
    $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
      'link' => 1,
    );
    $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
      3 => 'OR',
    );
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'news' => 'news',
    );
    $handler->display->display_options['filters']['type']['group'] = 1;
    /* Filter criterion: Workbench Moderation: Published */
    $handler->display->display_options['filters']['published']['id'] = 'published';
    $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['published']['field'] = 'published';
    $handler->display->display_options['filters']['published']['value'] = '1';
    $handler->display->display_options['filters']['published']['group'] = 1;
    /* Filter criterion: Content: Language */
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
    /* Filter criterion: Content: Group content visibility (group_content_access) */
    $handler->display->display_options['filters']['group_content_access_value']['id'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['table'] = 'field_data_group_content_access';
    $handler->display->display_options['filters']['group_content_access_value']['field'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['group_content_access_value']['group'] = 3;
    /* Filter criterion: Content: Groups audience (og_group_ref) */
    $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
    $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
    $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 3;
    $handler->display->display_options['path'] = 'news_public';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'News';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;


  }
}

