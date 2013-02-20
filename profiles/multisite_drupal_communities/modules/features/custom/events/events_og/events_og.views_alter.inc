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
    $handler->display->display_options['path'] = 'community/calendar';
  }
}

