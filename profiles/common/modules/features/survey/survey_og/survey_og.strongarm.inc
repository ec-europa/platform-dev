<?php

/**
 * @file
 * Code for the Survey og strongarm file.
 */

/**
 * Implements hook_strongarm().
 */
function survey_og_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_group_type_webform';
  $strongarm->value = 'omitted';
  $export['og_group_type_webform'] = $strongarm;

  return $export;
}
