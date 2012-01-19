<?php
// $Id$

/**
 * @file
 * This file describes the Views components provided by the ecas_extra module.
 */

function ecas_extra_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'ecas_extra') .'/includes',
    ),
    'handlers' => array(
      'ecas_extra_handler_field_user_is_denied' => array(
        'parent' => 'views_handler_field_boolean',
        'path' => drupal_get_path('module', 'ecas_extra') .'/includes',
        'file' => 'ecas_extra_handler_field_user_is_denied.inc',
      ),
      'ecas_extra_handler_filter_user_is_denied' => array(
        'parent' => 'views_handler_filter_in_operator',
        'path' => drupal_get_path('module', 'ecas_extra') .'/includes',
        'file' => 'ecas_extra_handler_filter_user_is_denied.inc',
      ),
    ),
  );
}

function ecas_extra_views_data() {
  $data['users']['user_denied'] = array(
    'title' => t('Denied'),
    'help' => t('Whether a user has been denied or not.'),
    'group' => t('User'),
    'field' => array(
      'handler' => 'ecas_extra_handler_field_user_is_denied',
      'parent' => 'views_handler_field_boolean',
      'path' => drupal_get_path('module', 'ecas_extra') .'/includes',
      'file' => 'ecas_extra_handler_field_user_is_denied.inc',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'ecas_extra_handler_filter_user_is_denied',
      'parent' => 'views_handler_filter_in_operator',
      'path' => drupal_get_path('module', 'ecas_extra') .'/includes',
      'file' => 'ecas_extra_handler_filter_user_is_denied.inc',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  return ($data);
}
