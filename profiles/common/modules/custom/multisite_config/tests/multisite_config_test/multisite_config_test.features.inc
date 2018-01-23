<?php

/**
 * @file
 * multisite_config_test.features.inc
 */

/**
 * Implements hook_node_info().
 */
function multisite_config_test_node_info() {
  $items = array(
    'test_with_fields' => array(
      'name' => t('Test with fields'),
      'base' => 'node_content',
      'description' => t('Test content type with fields.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'test_without_fields' => array(
      'name' => t('Test without fields'),
      'base' => 'node_content',
      'description' => t('Test content type without fields.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
