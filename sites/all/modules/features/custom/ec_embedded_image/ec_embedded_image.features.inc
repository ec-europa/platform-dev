<?php
/**
 * @file
 * ec_embedded_image.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ec_embedded_image_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}
