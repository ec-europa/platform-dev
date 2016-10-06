<?php
/**
 * @file
 * multisite_wysiwyg.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_wysiwyg_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
