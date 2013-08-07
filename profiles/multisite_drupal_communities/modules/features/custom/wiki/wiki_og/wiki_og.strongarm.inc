<?php
/**
 * @file
 * wiki_og.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wiki_og_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_wiki_pattern';
  $strongarm->value = 'community/[node:og_group_ref]/wiki/[node:title]';
  $export['pathauto_node_wiki_pattern'] = $strongarm;

  return $export;
}
