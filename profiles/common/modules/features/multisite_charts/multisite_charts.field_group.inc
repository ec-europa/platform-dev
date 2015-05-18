<?php
/**
 * @file
 * multisite_charts.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function multisite_charts_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_chart_content|node|chart|form';
  $field_group->group_name = 'group_chart_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'chart';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_chart_height',
      1 => 'field_chart_type',
      2 => 'field_chart_width',
      3 => 'field_chart_xml_data_source',
      4 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-chart-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_chart_content|node|chart|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_chart_metadata|node|chart|form';
  $field_group->group_name = 'group_chart_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'chart';
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
        'classes' => 'group-chart-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_chart_metadata|node|chart|form'] = $field_group;

  return $export;
}
