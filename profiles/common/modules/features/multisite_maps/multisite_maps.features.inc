<?php

/**
 * @file
 * multisite_maps.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_maps_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function multisite_maps_node_info() {
  $items = array(
    'map' => array(
      'name' => t('Map'),
      'base' => 'node_content',
      'description' => t('Use <em>maps</em> to display interactive, data driven maps.'),
      'has_title' => '1',
      'title_label' => t('Label / ID'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
