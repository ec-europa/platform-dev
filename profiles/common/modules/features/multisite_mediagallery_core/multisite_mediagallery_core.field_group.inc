<?php

/**
 * @file
 * multisite_mediagallery_core.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function multisite_mediagallery_core_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gallerymedia_content|node|gallerymedia|form';
  $field_group->group_name = 'group_gallerymedia_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gallerymedia';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_picture_upload',
      2 => 'field_video_upload',
      3 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gallerymedia-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_gallerymedia_content|node|gallerymedia|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gallerymedia_metadata|node|gallerymedia|form';
  $field_group->group_name = 'group_gallerymedia_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gallerymedia';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '10',
    'children' => array(
      0 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gallerymedia-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_gallerymedia_metadata|node|gallerymedia|form'] = $field_group;

  return $export;
}
