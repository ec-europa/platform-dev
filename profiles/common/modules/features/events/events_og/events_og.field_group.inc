<?php
/**
 * @file
 * events_og.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function events_og_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_community|node|event|form';
  $field_group->group_name = 'group_event_community';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Community',
    'weight' => '25',
    'children' => array(
      0 => 'group_content_access',
      1 => 'og_group_ref',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-event-community field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_event_community|node|event|form'] = $field_group;

  return $export;
}
