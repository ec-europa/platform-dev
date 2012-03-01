<?php
/**
 * @file
 * multisite_standard.features.inc
 */

/**
 * Implements hook_views_api().
 */
function multisite_standard_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}
