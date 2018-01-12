<?php

/**
 * @file
 * nexteuropa_event.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_event_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ne_event_content|node|nexteuropa_event|form';
  $field_group->group_name = 'group_ne_event_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_ne_body',
      1 => 'title_field',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ne-event-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ne_event_content|node|nexteuropa_event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ne_event_dates|node|nexteuropa_event|form';
  $field_group->group_name = 'group_ne_event_dates';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Dates',
    'weight' => '3',
    'children' => array(
      0 => 'field_dates',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ne-event-dates field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ne_event_dates|node|nexteuropa_event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ne_event_metadata|node|nexteuropa_event|form';
  $field_group->group_name = 'group_ne_event_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '1',
    'children' => array(
      0 => 'field_tags',
      1 => 'group_content_access',
      2 => 'og_group_ref',
      3 => 'field_event_type',
      4 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ne-event-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ne_event_metadata|node|nexteuropa_event|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Dates');
  t('Metadata');

  return $field_groups;
}
