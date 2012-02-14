<?php
/**
 * @file
 * ec_profiles.features.inc
 */

/**
 * Implements hook_views_api().
 */
function ec_profiles_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}
