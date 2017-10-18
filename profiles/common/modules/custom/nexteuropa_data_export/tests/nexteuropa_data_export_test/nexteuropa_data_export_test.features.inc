<?php

/**
 * @file
 * nexteuropa_data_export_test.features.inc
 */

/**
 * Implements hook_views_api().
 */
function nexteuropa_data_export_test_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function nexteuropa_data_export_test_node_info() {
  $items = array(
    'test_export' => array(
      'name' => t('Test export'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
