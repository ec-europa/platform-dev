<?php
/**
 * @file
 * multisite_forum_core.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function multisite_forum_core_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_discussion_content|node|discussion|form';
  $field_group->group_name = 'group_discussion_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'discussion';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'taxonomy_forums',
      2 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-discussion-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_discussion_content|node|discussion|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_discussion_metadata|node|discussion|form';
  $field_group->group_name = 'group_discussion_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'discussion';
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
        'classes' => 'group-discussion-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_discussion_metadata|node|discussion|form'] = $field_group;

  return $export;
}
