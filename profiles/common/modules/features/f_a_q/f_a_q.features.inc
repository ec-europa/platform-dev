<?php

/**
 * @file
 * f_a_q.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function f_a_q_ctools_plugin_api($module = NULL, $api = NULL) {
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
function f_a_q_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function f_a_q_node_info() {
  $items = array(
    'f_a_q' => array(
      'name' => t('F.A.Q'),
      'base' => 'node_content',
      'description' => t('Frequently Asked Questions'),
      'has_title' => '1',
      'title_label' => t('Question'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
