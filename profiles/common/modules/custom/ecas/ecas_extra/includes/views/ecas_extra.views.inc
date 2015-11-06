<?php

/**
 * @file
 * This file describes the Views components provided by the ecas_extra module.
 */

/**
 * Implements hook_views_data().
 */
function ecas_extra_views_data() {
  $data['users']['user_denied'] = array(
    'title' => t('Denied'),
    'help' => t('Whether a user has been denied or not.'),
    'group' => t('User'),
    'field' => array(
      'handler' => 'ecas_extra_handler_field_user_is_denied',
      'parent' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'ecas_extra_handler_filter_user_is_denied',
      'parent' => 'views_handler_filter_in_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  return ($data);
}
