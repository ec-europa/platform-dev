<?php

/**
 * @file
 * multisite_translations.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function multisite_translations_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_job_reference'.
  $field_bases['field_job_reference'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_job_reference',
    'foreign keys' => array(
      'tmgmt_job' => array(
        'columns' => array(
          'target_id' => 'tjid',
        ),
        'table' => 'tmgmt_job',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 1,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(),
      ),
      'target_type' => 'tmgmt_job',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
