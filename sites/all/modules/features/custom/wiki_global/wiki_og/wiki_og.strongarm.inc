<?php
/**
 * @file
 * wiki.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wiki_og_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_group_type_wiki';
  $strongarm->value = 'omitted';
  $export['og_group_type_wiki'] = $strongarm;
  
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_wiki_pattern';
  $strongarm->value = 'community/[node:group_audience]/wiki/[node:title]';
  $export['pathauto_node_wiki_pattern'] = $strongarm;

  return $export;
}

