<?php

/**
 * @file
 * events_og.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function events_og_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_event_pattern';
  $strongarm->value = 'community/[node:og_group_ref]/event/[node:title]';
  $export['pathauto_node_event_pattern'] = $strongarm;

  return $export;
}
