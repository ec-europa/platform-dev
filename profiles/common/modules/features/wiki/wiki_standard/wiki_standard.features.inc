<?php

/**
 * @file
 * wiki_standard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wiki_standard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
