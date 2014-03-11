<?php
/**
 * @file
 * multisite_mediagallery_community.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function multisite_mediagallery_community_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gallerymedia_community|node|gallerymedia|form';
  $field_group->group_name = 'group_gallerymedia_community';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gallerymedia';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Community',
    'weight' => '5',
    'children' => array(
      0 => 'group_content_access',
      1 => 'og_group_ref',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gallerymedia-community field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_gallerymedia_community|node|gallerymedia|form'] = $field_group;

  return $export;
}
