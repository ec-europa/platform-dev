<?php
/**
 * @file
 * links.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function links_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function links_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function links_node_info() {
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
  return $items;
}
