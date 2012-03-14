<?php
/**
 * @file
 * ideation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ideation_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ideation_node_info() {
  $items = array(
    'idea_site' => array(
      'name' => t('Idea'),
      'base' => 'node_content',
      'description' => t('A submission of an idea that can be posted, voted on, and commented upon.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
