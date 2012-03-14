<?php
// @TODO Upgrade to D7 handlers
// $Id$

/**
 * Implementation of hook_views_handlers().
 */
 /*
function ideation_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'ideation') . '/views',
    ),
    'handlers' => array(
      'ideation_views_handler_field_value_pluralcount' => array(
        'parent' => 'views_handler_field',
      ),
      'ideation_views_handler_field_value_fiveavg' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
*/

/**
 * Implementation of hook_views_data()
 */
/*
function ideation_views_data() {
  // Plural handler for vote count.
  $data['votingapi_vote']['value_plural'] = array(
    'title' => t('Count, plural handled'),
    'help' => t('Display number of votes cast, plural handled'),
    'real field' => 'value',
    'field' => array(
      'handler' => 'ideation_views_handler_field_value_pluralcount',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['votingapi_cache']['value_plural'] = array(
    'title' => t('Count, plural handled'),
    'help' => t('Display number of votes cast, plural handled'),
    'real field' => 'value',
    'field' => array(
      'handler' => 'ideation_views_handler_field_value_pluralcount',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // 0 to 5 handler for vote average
  $data['votingapi_vote']['value_five'] = array(
    'title' => t('Scale of five'),
    'help' => t('Display average vote out of five.'),
    'real field' => 'value',
    'field' => array(
      'handler' => 'ideation_views_handler_field_value_fiveavg',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['votingapi_cache']['value_five'] = array(
    'title' => t('Scale of five'),
    'help' => t('Display average vote out of five.'),
    'real field' => 'value',
    'field' => array(
      'handler' => 'ideation_views_handler_field_value_fiveavg',
      'click sortable' => TRUE
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  ); 
  
  return $data;
}
*/