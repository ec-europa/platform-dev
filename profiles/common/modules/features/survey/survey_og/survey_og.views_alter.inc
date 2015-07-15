<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function survey_og_views_default_views_alter(&$views) {
  if (array_key_exists('surveys_list', $views)) {
    $view=$views['surveys_list'];

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
    
    $handler = $view->new_display('page', 'Page', 'page_1');
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
    $handler->display->display_options['path'] = 'survey';    
    


    /* Display: survey_public */
    $handler = $view->new_display('page', 'survey_public', 'page_2');
    
    $handler->display->display_options['defaults']['empty'] = FALSE;
    /* No results behavior: Global: Text area */
    $handler->display->display_options['empty']['area']['id'] = 'area';
    $handler->display->display_options['empty']['area']['table'] = 'views';
    $handler->display->display_options['empty']['area']['field'] = 'area';
    $handler->display->display_options['empty']['area']['empty'] = TRUE;
    $handler->display->display_options['empty']['area']['content'] = 'No content found.';
    $handler->display->display_options['empty']['area']['format'] = 'full_html';
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    /* Field: Content: Body */
    $handler->display->display_options['fields']['body']['id'] = 'body';
    $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
    $handler->display->display_options['fields']['body']['field'] = 'body';
    /* Field: Content: Groups audience */
    $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
    $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
    $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
    $handler->display->display_options['fields']['og_group_ref']['label'] = 'Community';
    $handler->display->display_options['fields']['og_group_ref']['hide_empty'] = TRUE;
    $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
      'link' => 1,
    );
    $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
    /* Field: Webform: Webform results link */
    $handler->display->display_options['fields']['webform_results']['id'] = 'webform_results';
    $handler->display->display_options['fields']['webform_results']['table'] = 'node';
    $handler->display->display_options['fields']['webform_results']['field'] = 'webform_results';
    /* Field: Webform: Webform submission count */
    $handler->display->display_options['fields']['webform_submission_count_node']['id'] = 'webform_submission_count_node';
    $handler->display->display_options['fields']['webform_submission_count_node']['table'] = 'node';
    $handler->display->display_options['fields']['webform_submission_count_node']['field'] = 'webform_submission_count_node';
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
      3 => 'OR',
    );
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = '1';
    $handler->display->display_options['filters']['status']['group'] = 1;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'webform' => 'webform',
    );
    $handler->display->display_options['filters']['type']['group'] = 1;

    /* Filter criterion: Content: Groups audience (og_group_ref) */
    $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
    $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
    $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
    $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 3;
    /* Filter criterion: Content: Group content visibility (group_content_access) */
    $handler->display->display_options['filters']['group_content_access_value']['id'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['table'] = 'field_data_group_content_access';
    $handler->display->display_options['filters']['group_content_access_value']['field'] = 'group_content_access_value';
    $handler->display->display_options['filters']['group_content_access_value']['value'] = array(
      1 => '1',
    );
    $handler->display->display_options['filters']['group_content_access_value']['group'] = 3;
    $handler->display->display_options['path'] = 'survey_public';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Surveys';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;


    
  }
}

