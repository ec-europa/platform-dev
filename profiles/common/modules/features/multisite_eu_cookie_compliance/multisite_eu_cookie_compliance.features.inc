<?php

/**
 * @file
 * multisite_eu_cookie_compliance.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_eu_cookie_compliance_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
