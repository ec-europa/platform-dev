<?php

/**
 * @file
 * Helpers for the install scripts.
 *
 */

/**
 * Get current module version.
 */
function _multisite_business_indicators_community_get_version() {
  $path = drupal_get_path('module', 'multisite_business_indicators_community') . '/multisite_business_indicators_community.info';
  $info = drupal_parse_info_file($path);
  return $info['version'];
}