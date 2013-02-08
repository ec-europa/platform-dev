<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function links_og_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('links', $views)) {
    $view=$views['links'];

    /* Display: Master */
    $handler = $view->display['page']->handler;
    $handler->display->display_options['access']['type'] = 'og_context';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['path'] = 'community/links';
    $handler->display->display_options['menu']['type'] = 'none';

    /* Relationship: Group membership: Node group membership */
    $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
    $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
    $handler->display->display_options['relationships']['og_membership_rel']['required'] = 0;

    /* Contextual filter: OG membership: Group gid */
    $handler->display->display_options['arguments']['group']['id'] = 'group';
    $handler->display->display_options['arguments']['group']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['group']['field'] = 'group';
    $handler->display->display_options['arguments']['group']['relationship'] = 'og_membership_rel';
    $handler->display->display_options['arguments']['group']['default_action'] = 'default';
    $handler->display->display_options['arguments']['group']['default_argument_type'] = 'og_context';
    $handler->display->display_options['arguments']['group']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['group']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['group']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['group']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['group']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['group']['not'] = 0;
  }
}
