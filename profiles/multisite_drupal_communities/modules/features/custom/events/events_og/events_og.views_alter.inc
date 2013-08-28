<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function events_og_views_default_views_alter(&$views) {
  if (array_key_exists('calendar', $views)) {
    $view=$views['calendar'];

    $handler = $view->display['month']->handler;
    unset($handler->display->display_options['menu']);
    unset($handler->display->display_options['tab_options']);
    
    /* Display: Calendar */
    $handler = $view->new_display('page', 'Calendar', 'page_1');
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    /* Relationship: OG membership: OG membership from Node */
    $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
    $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
    
    /* Contextual filter: Date: Date (node) */
    $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
    $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
    $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
    $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
    $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
      'field_data_field_event_date.field_event_date_value' => 'field_data_field_event_date.field_event_date_value',
    );

    /* Display: events_public */
    $handler = $view->new_display('page', 'events_public', 'page_2');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Events';
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['filter_groups']['groups'] = array(
      1 => 'AND',
      2 => 'OR',
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
      'event' => 'event',
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
    $handler->display->display_options['path'] = 'events_public';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'Events';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;

  }
}

