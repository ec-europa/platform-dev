<?php
/**
 * @file
 * communities.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function communities_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function communities_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function communities_node_info() {
  $items = array(
    'community' => array(
      'name' => t('community'),
      'base' => 'node_content',
      'description' => t('content type to handle groups'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
