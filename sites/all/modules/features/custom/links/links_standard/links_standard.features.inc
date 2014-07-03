<?php
/**
 * @file
 * links_standard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function links_standard_ctools_plugin_api() {
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
 * Implements hook_views_api().
 */
function links_standard_views_api() {
  return array("api" => "3.0");
}
