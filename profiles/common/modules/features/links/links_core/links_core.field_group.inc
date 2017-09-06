<?php

/**
 * @file
 * links_core.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function links_core_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_links_content|node|links|form';
  $field_group->group_name = 'group_links_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'links';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_link',
      1 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-links-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_links_content|node|links|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_links_metadata|node|links|form';
  $field_group->group_name = 'group_links_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'links';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '10',
    'children' => array(
      0 => 'field_tags',
      1 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-link-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_links_metadata|node|links|form'] = $field_group;

  return $export;
}
