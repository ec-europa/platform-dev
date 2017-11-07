<?php

/**
 * @file
 * multisite_translations.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function multisite_translations_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-job_translation_log-field_job_reference'.
  $field_instances['message-job_translation_log-field_job_reference'] = array(
    'bundle' => 'job_translation_log',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_job_reference',
    'label' => 'job reference',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('job reference');

  return $field_instances;
}
