<?php
/**
 * @file
 * multisite_settings_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function multisite_settings_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'content/welcome-your-site';
  $export['site_frontpage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_default';
  $strongarm->value = 'ec_resp';
  $export['theme_default'] = $strongarm;

  return $export;
}
