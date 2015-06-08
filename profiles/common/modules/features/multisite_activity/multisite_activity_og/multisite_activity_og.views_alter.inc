<?php

/**
 * @file
 * Alters the view for news feature.
 */

/**
* Implementation of hook_views_default_views_alter().
*/
function multisite_activity_og_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('multisite_activity', $views)) {
    $view = $views['multisite_activity'];


    /* Display: Defaults */
    $handler = $view->display['default']->handler;
    $handler->display->display_options['title'] = 'Group recent activity';

    /* Relationship: OG membership: Message from OG membership */
    $handler->display->display_options['relationships']['og_membership_related_message']['id'] = 'og_membership_related_message';
    $handler->display->display_options['relationships']['og_membership_related_message']['table'] = 'og_membership';
    $handler->display->display_options['relationships']['og_membership_related_message']['field'] = 'og_membership_related_message';

    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'og_context';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';


    /* Display: News list page */
    $handler = $view->display['page_1']->handler;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    /* Contextual filter: OG membership: Group ID */
    $handler->display->display_options['arguments']['gid']['id'] = 'gid';
    $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
    $handler->display->display_options['arguments']['gid']['field'] = 'gid';
    $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_related_message';
    $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';

    /* Display: Block */
    $handler = $view->display['block_1']->handler;
    $handler->display->display_options['pager']['options']['items_per_page'] = '30';

  }
}

