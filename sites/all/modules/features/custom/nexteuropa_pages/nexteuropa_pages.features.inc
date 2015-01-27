<?php
/**
 * @file
 * nexteuropa_pages.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_pages_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}
