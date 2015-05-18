<?php

/**
 * @file
 * Helpers for the install scripts.
 */

/**
 * Returns the current module version.
 *
 * @return string
 *   The current version of the module.
 */
function _multisite_multilingual_references_get_version() {
  $module = basename(__FILE__, ".install.inc");
  $path = drupal_get_path('module', $module) . '/' . $module . '.info';
  $info = drupal_parse_info_file($path);
  return $info['version'];
}
