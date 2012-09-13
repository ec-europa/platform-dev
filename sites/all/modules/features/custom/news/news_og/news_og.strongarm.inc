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
  $strongarm->name = 'og_group_type_news';
  $strongarm->value = 'omitted';
  $export['og_group_type_news'] = $strongarm;

  return $export;
}

