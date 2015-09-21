<?php
/**
 * @file
 * language_selector_page_settings.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function language_selector_page_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
