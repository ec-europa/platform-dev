<?php

/**
 * @file
 * nexteuropa_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_event_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
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
function nexteuropa_event_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function nexteuropa_event_node_info() {
  $items = array(
    'nexteuropa_event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Event content type for Nexteuropa'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
