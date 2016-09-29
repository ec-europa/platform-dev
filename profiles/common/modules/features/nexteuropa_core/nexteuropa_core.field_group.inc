<?php

/**
 * @file
 * nexteuropa_core.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_core_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_community_content|node|community|form';
  $field_group->group_name = 'group_community_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'community';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'group_access',
      2 => 'group_group',
      3 => 'title_field',
      4 => 'path',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-community-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_community_content|node|community|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_community_metadata|node|community|form';
  $field_group->group_name = 'group_community_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'community';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '1',
    'children' => array(
      0 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-community-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_community_metadata|node|community|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Metadata');

  return $field_groups;
}
