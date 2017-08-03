<?php

/**
 * @file
 * multisite_charts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_charts_ctools_plugin_api($module = NULL, $api = NULL) {
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
function multisite_charts_node_info() {
  $items = array(
    'chart' => array(
      'name' => t('Chart'),
      'base' => 'node_content',
      'description' => t('Use <em>charts</em> to display graphs out of your data.'),
      'has_title' => '1',
      'title_label' => t('Label / ID'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
