<?php

/**
 * @file
 * Helpers for the install scripts.
 *
 */

/**
 * Get current module version.
 */
function _multisite_forum_community_get_version() {
  $path = drupal_get_path('module', 'multisite_forum_community') . '/multisite_forum_community.info';
  $info = drupal_parse_info_file($path);
  return $info['version'];
}