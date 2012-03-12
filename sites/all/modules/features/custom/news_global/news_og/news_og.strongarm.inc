<?php
/**
 * @file
 * news.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function news_og_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_news_pattern';
  $strongarm->value = 'community/[node:group_audience]/news/[node:title]';
  $export['pathauto_node_news_pattern'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_group_type_news';
  $strongarm->value = 'omitted';
  $export['og_group_type_news'] = $strongarm;

  return $export;
}

