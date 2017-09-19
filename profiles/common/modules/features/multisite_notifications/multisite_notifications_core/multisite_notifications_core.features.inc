<?php

/**
 * @file
 * multisite_notifications_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_notifications_core_ctools_plugin_api($module = NULL, $api = NULL) {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
