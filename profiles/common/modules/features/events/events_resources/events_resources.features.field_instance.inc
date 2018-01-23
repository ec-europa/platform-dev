<?php

/**
 * @file
 * events_resources.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function events_resources_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-event-field_resource'.
  $field_instances['node-event-field_resource'] = array(
    'bundle' => 'event',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_plain',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_resource',
    'label' => 'Resource',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 220,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Resource');

  return $field_instances;
}
