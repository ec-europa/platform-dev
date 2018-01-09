<?php

/**
 * @file
 * survey_og.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function survey_og_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
