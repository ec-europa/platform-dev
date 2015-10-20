<?php
/**
 * @file
 * links_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function links_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function links_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function links_core_node_info() {
  $items = array(
    'links' => array(
      'name' => t('Links'),
      'base' => 'node_content',
      'description' => t('Share links within your group'),
      'has_title' => '1',
      'title_label' => t('Link Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
