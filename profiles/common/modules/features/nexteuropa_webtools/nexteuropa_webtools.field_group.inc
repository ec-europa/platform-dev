<?php
/**
 * @file
 * nexteuropa_webtools.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_webtools_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_custom_js_settings|bean|webtools|form';
  $field_group->group_name = 'group_custom_js_settings';
  $field_group->entity_type = 'bean';
  $field_group->bundle = 'webtools';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Custom js',
    'weight' => '8',
    'children' => array(
      'field_custom_js_link',
      'field_custom_js_status',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-custom-js-settings field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_custom_js_settings|bean|webtools|form'] = $field_group;

  return $export;
}
