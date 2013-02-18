<?php
/**
 * @file
 * e_library.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function e_library_og_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_document_pattern';
  $strongarm->value = 'community/[node:group_audience]/document/[node:title]';
  $export['pathauto_node_document_pattern'] = $strongarm;

  return $export;
}
