<?php

/**
 * @file
 * idea_core.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function idea_core_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_idea_content|node|idea|form';
  $field_group->group_name = 'group_idea_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'idea';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_watching',
      2 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-idea-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_idea_content|node|idea|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_idea_metadata|node|idea|form';
  $field_group->group_name = 'group_idea_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'idea';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '10',
    'children' => array(
      0 => 'field_categories_taxonomy',
      1 => 'field_status_taxonomy',
      2 => 'field_tags',
      3 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-idea-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_idea_metadata|node|idea|form'] = $field_group;

  return $export;
}
