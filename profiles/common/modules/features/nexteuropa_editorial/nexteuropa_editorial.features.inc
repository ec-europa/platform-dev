<?php
/**
 * @file
 * nexteuropa_editorial.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_editorial_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function nexteuropa_editorial_node_info() {
  $items = array(
    'editorial_team' => array(
      'name' => t('Editorial team'),
      'base' => 'node_content',
      'description' => t('Editorial teams.'),
      'has_title' => '1',
      'title_label' => t('Editorial team name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
