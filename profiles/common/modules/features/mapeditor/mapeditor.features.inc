<?php
/**
 * @file
 * mapeditor.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mapeditor_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function mapeditor_node_info() {
  $items = array(
    'mapeditor_map' => array(
      'name' => t('Map (by mapeditor)'),
      'base' => 'node_content',
      'description' => t('The map type allows creating a map in simple steps.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
