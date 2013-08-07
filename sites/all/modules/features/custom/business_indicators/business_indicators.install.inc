<?php

/**
 * @file
 * Helpers for the install scripts.
 *
 */

/**
 * Get current module version.
 */
function _business_indicators_get_version() {
  $path = drupal_get_path('module', 'business_indicators') . '/business_indicators.info';
  $info = drupal_parse_info_file($path);
  return $info['version'];
}