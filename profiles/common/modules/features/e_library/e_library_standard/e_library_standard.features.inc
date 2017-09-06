<?php

/**
 * @file
 * e_library_standard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function e_library_standard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
