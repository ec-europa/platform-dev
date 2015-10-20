<?php
/**
 * @file
 * links_standard.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function links_standard_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_links_pattern';
  $strongarm->value = 'links/[node:title]';
  $export['pathauto_node_links_pattern'] = $strongarm;

  return $export;
}
