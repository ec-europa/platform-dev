<?php
/**
 * @file
 * idea_standard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function idea_standard_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function idea_standard_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function idea_standard_node_info() {
  $items = array(
    'wiki' => array(
      'name' => t('Idea'),
      'base' => 'node_content',
      'description' => t('content for the idea feature'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

