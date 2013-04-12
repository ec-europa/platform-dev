<?php
/**
 * @file
 * multisite_notifications_og.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_notifications_og_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
