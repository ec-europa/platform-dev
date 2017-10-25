<?php
/**
 * @file
 * nexteuropa_editorial.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function nexteuropa_editorial_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|editorial_team|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'editorial_team';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_group',
        1 => 'group_access',
        2 => 'og_roles_permissions',
        3 => 'body',
      ),
    ),
    'fields' => array(
      'group_group' => 'ds_content',
      'group_access' => 'ds_content',
      'og_roles_permissions' => 'ds_content',
      'body' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|editorial_team|full'] = $ds_layout;

  return $export;
}
