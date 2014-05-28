<?php
/**
 * @file
 * multisite_registration_core.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function multisite_registration_core_field_default_fields() {
  $fields = array();

  // Exported field: 'node-event-field_registration'.
  $fields['node-event-field_registration'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_registration',
      'foreign keys' => array(
        'registration_type' => array(
          'columns' => array(
            'registration_type' => 'name',
          ),
          'table' => 'registration_type',
        ),
      ),
      'indexes' => array(
        'registration_type' => array(
          0 => 'registration_type',
        ),
      ),
      'locked' => '0',
      'module' => 'registration',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'registration',
    ),
    'field_instance' => array(
      'bundle' => 'event',
      'default_value' => array(
        0 => array(
          'registration_type' => 'event_registration',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'registration',
          'settings' => array(
            'label' => ' ',
          ),
          'type' => 'registration_default',
          'weight' => 6,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_registration',
      'label' => 'registration',
      'required' => 0,
      'settings' => array(
        'default_registration_settings' => array(
          'capacity' => '100',
          'reminder' => array(
            'reminder_settings' => array(
              'reminder_date' => NULL,
              'reminder_template' => '',
            ),
            'send_reminder' => 0,
          ),
          'scheduling' => array(
            'close' => NULL,
            'open' => NULL,
          ),
          'settings' => array(
            'confirmation' => 'Registration has been saved.',
            'from_address' => 'DIGIT-FPFIS-SUPPORT@ec.europa.eu',
            'maximum_spaces' => '2',
            'multiple_registrations' => 0,
            'registration_entity_access_roles' => array(
              2 => '2',
              3 => 0,
              4 => 0,
              5 => 0,
            ),
            'registration_waitlist_capacity' => '20',
            'registration_waitlist_enable' => 0,
          ),
          'status' => 1,
        ),
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'registration',
        'settings' => array(),
        'type' => 'registration_select',
        'weight' => '221',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('registration');

  return $fields;
}
