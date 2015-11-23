<?php
/**
 * @file
 * multisite_drupal_toolbox_test.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function multisite_drupal_toolbox_test_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'multisite_drupal_toolbox_foobar';
  $strongarm->value = 'foo';
  $export['multisite_drupal_toolbox_foobar'] = $strongarm;

  return $export;
}
