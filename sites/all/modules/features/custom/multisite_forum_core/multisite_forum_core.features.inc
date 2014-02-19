<?php
/**
 * @file
 * multisite_forum_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_forum_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}


/**
 * Implements hook_node_info().
 */
function multisite_forum_core_node_info() {
  $items = array(
    MULTISITE_FORUM_CT_NAME => array(
      'name' => t('Discussion'),
      'base' => 'node_content',
      'description' => t('A <em>discussion</em> starts a new discussion thread within a forum.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
