<?php

/**
 * @file
 * nexteuropa_mediagallery.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_mediagallery_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gallerymedia_content|node|nexteuropa_mediagallery|form';
  $field_group->group_name = 'group_gallerymedia_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_mediagallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_media_upload',
      1 => 'title_field',
      2 => 'field_ne_body',
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
  $field_groups['group_gallerymedia_content|node|nexteuropa_mediagallery|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gallerymedia_metadata|node|nexteuropa_mediagallery|form';
  $field_group->group_name = 'group_gallerymedia_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'nexteuropa_mediagallery';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '3',
    'children' => array(
      0 => 'field_tags',
      1 => 'group_content_access',
      2 => 'og_group_ref',
      3 => 'language',
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
  $field_groups['group_gallerymedia_metadata|node|nexteuropa_mediagallery|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Metadata');

  return $field_groups;
}
