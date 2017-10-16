<?php

/**
 * @file
 * nexteuropa_trackedchanges.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_trackedchanges_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
