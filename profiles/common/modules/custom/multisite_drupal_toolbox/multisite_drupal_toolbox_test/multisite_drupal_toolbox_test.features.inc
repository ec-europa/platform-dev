<?php
/**
 * @file
 * multisite_drupal_toolbox_test.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_drupal_toolbox_test_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
