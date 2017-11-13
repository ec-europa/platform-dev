<?php

/**
 * @file
 * e_library_og.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function e_library_og_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_document_community|node|document|form';
  $field_group->group_name = 'group_document_community';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'document';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Community',
    'weight' => '20',
    'children' => array(
      0 => 'group_content_access',
      1 => 'og_group_ref',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-document-community field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_document_community|node|document|form'] = $field_group;

  return $export;
}
