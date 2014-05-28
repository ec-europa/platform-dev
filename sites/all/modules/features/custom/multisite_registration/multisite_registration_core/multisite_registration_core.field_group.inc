<?php
/**
 * @file
 * multisite_registration_core.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function multisite_registration_core_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_registration|node|event|form';
  $field_group->group_name = 'group_registration';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Registration',
    'weight' => '224',
    'children' => array(
      0 => 'field_registration',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-registration field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_registration1|node|event|form'] = $field_group;

  return $export;
}
