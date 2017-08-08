<?php
/**
 * @file
 * ecas_env.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ecas_env_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ecas_pages_method';
  $strongarm->value = 1;
  $export['ecas_pages_method'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ecas_profile_core_enabled';
  $strongarm->value = TRUE;
  $export['ecas_profile_core_enabled'] = $strongarm;

  return $export;
}
