<?php
/**
 * @file
 * gallerymedia_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gallerymedia_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gallerymedia_core_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function gallerymedia_core_node_info() {
  $items = array(
    'gallerymedia' => array(
      'name' => t('GalleryMedia'),
      'base' => 'node_content',
      'description' => t('A Gallery of Media.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
