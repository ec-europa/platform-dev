<?php
/**
 * @file
 * nexteuropa_faq.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_faq_ctools_plugin_api($module = NULL, $api = NULL) {
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
function nexteuropa_faq_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function nexteuropa_faq_node_info() {
  $items = array(
    'nexteuropa_faq' => array(
      'name' => t('FAQ'),
      'base' => 'node_content',
      'description' => t('FAQ content for Nexteuropa'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
