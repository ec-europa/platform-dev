<?php
/**
 * @file
 * multisite_maps.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function multisite_maps_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_map_content|node|map|form';
  $field_group->group_name = 'group_map_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'map';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '10',
    'children' => array(
      0 => 'field_map_height',
      1 => 'field_map_type',
      2 => 'field_map_width',
      3 => 'field_map_xml_data_source',
      4 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-map-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_map_content|node|map|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_map_metadata|node|map|form';
  $field_group->group_name = 'group_map_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'map';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '20',
    'children' => array(
      0 => 'language',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-map-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_news_metadata|node|map|form'] = $field_group;

  return $export;
}
