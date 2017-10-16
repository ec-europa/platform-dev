<?php

/**
 * @file
 * Provides support for the Views module.
 */

/**
 * Implements hook_views_data().
 */
function nexteuropa_faq_views_data() {
  $data = array();
  $data['views']['f_a_q_collapsible_menu'] = array(
    'title' => t('FAQ Collapsible Menu'),
    'help' => t('Displays (expand all /collapse all) menu for the list of FAQ.'),
    'area' => array(
      'handler' => 'views_handler_area_nexteuropa_faq_collapsible_menu',
    ),
  );

  return $data;
}
