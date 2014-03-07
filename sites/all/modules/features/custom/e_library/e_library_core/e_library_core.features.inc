<?php
/**
 * @file
 * e_library_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function e_library_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function e_library_core_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function e_library_core_node_info() {
  $items = array(
    'document' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('Upload document'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
