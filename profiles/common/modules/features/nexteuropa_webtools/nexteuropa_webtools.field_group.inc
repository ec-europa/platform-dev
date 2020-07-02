<?php

/**
 * @file
 * nexteuropa_webtools.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nexteuropa_webtools_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_custom_css_settings|bean|webtools|form';
  $field_group->group_name = 'group_custom_css_settings';
  $field_group->entity_type = 'bean';
  $field_group->bundle = 'webtools';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Custom css',
    'weight' => '4',
    'children' => array(
      0 => 'field_custom_css_status',
      2 => 'field_custom_css_link',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-custom-css-settings field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_custom_css_settings|bean|webtools|form'] = $field_group;

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
    'weight' => '3',
    'children' => array(
      0 => 'field_custom_js_file',
      1 => 'field_custom_js_link',
      2 => 'field_custom_js_status',
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
  $field_groups['group_custom_js_settings|bean|webtools|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Custom css');
  t('Custom js');

  return $field_groups;
}
