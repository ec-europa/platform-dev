<?php
/**
 * @file
 * e_library_og.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function e_library_og_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
