<?php
/**
 * @file
 * nexteuropa_news.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_news_ctools_plugin_api($module = NULL, $api = NULL) {
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
function nexteuropa_news_node_info() {
  $items = array(
    'nexteuropa_news' => array(
      'name' => t('News'),
      'base' => 'node_content',
      'description' => t('News content type for NextEuropa'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
