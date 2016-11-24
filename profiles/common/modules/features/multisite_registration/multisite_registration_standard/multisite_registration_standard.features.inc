<?php

/**
 * @file
 * multisite_registration_standard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_registration_standard_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
