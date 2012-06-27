<?php
/**
 * @file
 * eaq_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eaq_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function eaq_feature_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function eaq_feature_node_info() {
  $items = array(
    'ask_a_question' => array(
      'name' => t('Ask a Question'),
      'base' => 'node_content',
      'description' => t('Ask a Question'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
