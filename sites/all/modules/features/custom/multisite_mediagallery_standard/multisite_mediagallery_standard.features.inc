<?php
/**
 * @file
 * multisite_mediagallery_standard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_mediagallery_standard_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
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
function multisite_mediagallery_standard_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("api" => "3.0");
  }
}
