<?php
/**
* Implementation of hook_views_default_views_alter().
*/
function e_library_og_views_default_views_alter(&$views) {
  if (array_key_exists('e_library', $views)) {
    $view=$views['e_library'];

    /* Display: Master */
    $handler = $view->display['default']->handler;

    $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
    $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';

    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'og_context';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
    );


    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page');
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    $handler->display->display_options['path'] = 'e_library';


    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    

    /* Display: e_library_public */
    $handler = $view->new_display('page', 'e_library_public', 'page_1');
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    /* Relationship: Content: Author */
    $handler->display->display_options['relationships']['uid']['id'] = 'uid';
    $handler->display->display_options['relationships']['uid']['table'] = 'node';
    $handler->display->display_options['relationships']['uid']['field'] = 'uid';
    /* Relationship: File Usage: File */
    $handler->display->display_options['relationships']['node_to_file']['id'] = 'node_to_file';
    $handler->display->display_options['relationships']['node_to_file']['table'] = 'file_usage';
    $handler->display->display_options['relationships']['node_to_file']['field'] = 'node_to_file';
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: File: Mime type */
    $handler->display->display_options['fields']['filemime']['id'] = 'filemime';
    $handler->display->display_options['fields']['filemime']['table'] = 'file_managed';
    $handler->display->display_options['fields']['filemime']['field'] = 'filemime';
    $handler->display->display_options['fields']['filemime']['relationship'] = 'node_to_file';
    $handler->display->display_options['fields']['filemime']['label'] = 'File type';
    $handler->display->display_options['fields']['filemime']['exclude'] = TRUE;
    $handler->display->display_options['fields']['filemime']['filemime_image'] = TRUE;
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
    $handler->display->display_options['fields']['title']['alter']['text'] = '[filemime] [title]';
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['relationship'] = 'uid';
    $handler->display->display_options['fields']['name']['label'] = 'Author';
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
    $handler->display->display_options['fields']['count']['element_class'] = 'hidden-phone';
    $handler->display->display_options['fields']['count']['element_label_class'] = 'hidden-phone';
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
      'document' => 'document',
    );
    $handler->display->display_options['filters']['type']['group'] = 1;
    /* Filter criterion: Workbench Moderation: Published */
    $handler->display->display_options['filters']['published']['id'] = 'published';
    $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
    $handler->display->display_options['filters']['published']['field'] = 'published';
    $handler->display->display_options['filters']['published']['value'] = '1';
    $handler->display->display_options['filters']['published']['group'] = 1;
    /* Filter criterion: Content: Media tags (field_media_tags) */
    $handler->display->display_options['filters']['field_media_tags_tid']['id'] = 'field_media_tags_tid';
    $handler->display->display_options['filters']['field_media_tags_tid']['table'] = 'field_data_field_media_tags';
    $handler->display->display_options['filters']['field_media_tags_tid']['field'] = 'field_media_tags_tid';
    $handler->display->display_options['filters']['field_media_tags_tid']['group'] = 1;
    $handler->display->display_options['filters']['field_media_tags_tid']['exposed'] = TRUE;
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['operator_id'] = 'field_media_tags_tid_op';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['label'] = 'Media tags';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['operator'] = 'field_media_tags_tid_op';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['identifier'] = 'field_media_tags_tid';
    $handler->display->display_options['filters']['field_media_tags_tid']['expose']['remember_roles'] = array(
      2 => '2',
      1 => 0,
      3 => 0,
      4 => 0,
      5 => 0,
    );
    $handler->display->display_options['filters']['field_media_tags_tid']['type'] = 'select';
    $handler->display->display_options['filters']['field_media_tags_tid']['vocabulary'] = 'media_tags';
    $handler->display->display_options['filters']['field_media_tags_tid']['hierarchy'] = 1;
    /* Filter criterion: File: Mime type */
    $handler->display->display_options['filters']['filemime']['id'] = 'filemime';
    $handler->display->display_options['filters']['filemime']['table'] = 'file_managed';
    $handler->display->display_options['filters']['filemime']['field'] = 'filemime';
    $handler->display->display_options['filters']['filemime']['relationship'] = 'node_to_file';
    $handler->display->display_options['filters']['filemime']['operator'] = '!=';
    $handler->display->display_options['filters']['filemime']['value'] = 'IMAGE/JPEGG';
    $handler->display->display_options['filters']['filemime']['group'] = 1;

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
    $handler->display->display_options['path'] = 'e_library_public';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'E-library';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;


    
  }
  
  
  if (array_key_exists('elibrary_browser_tab', $views)) {
    $view=$views['elibrary_browser_tab'];
    
    $handler = $view->display['default']->handler;
    
    /* Relationship: OG membership: OG membership from Node */
    $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
    $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['relationship'] = 'file_to_node';
    
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
    
    $handler = $view->display['media_browser_1']->handler;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'php';
    $handler->display->display_options['arguments']['gid']['default_argument_options']['code'] = 'return $_SESSION[\'og_context\'][\'gid\'];';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    
  }
  
}



































































