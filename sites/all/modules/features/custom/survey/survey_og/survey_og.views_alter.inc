<?php

/**
* Implementation of hook_views_default_views_alter().
*/
function survey_og_views_default_views_alter(&$views) {
  if (array_key_exists('surveys_list', $views)) {
    $view=$views['surveys_list'];
	 
    /* Display: Defaults */
    $handler = $view->new_display('default', 'Defaults', 'default');
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
    $handler->display->display_options['arguments']['group']['default_action'] = 'empty';
    $handler->display->display_options['arguments']['group']['default_argument_type'] = 'fixed';
    $handler->display->display_options['arguments']['group']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['group']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['group']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['group']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['group']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['group']['not'] = 0;
	
    /* Display: Latest News Block */
    $handler = $view->new_display('block', 'Latest News Block', 'block_1');
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

    /* Display: Community Top news */
    $handler = $view->new_display('block', 'Community Top news', 'block_2');
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

