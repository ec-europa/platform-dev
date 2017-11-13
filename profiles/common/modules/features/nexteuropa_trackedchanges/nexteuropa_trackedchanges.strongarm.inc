<?php

/**
 * @file
 * nexteuropa_trackedchanges.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nexteuropa_trackedchanges_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nexteuropa_trackedchanges_disable_track_on_create';
  $strongarm->value = 1;
  $export['nexteuropa_trackedchanges_disable_track_on_create'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nexteuropa_trackedchanges_tracking_status';
  $strongarm->value = 1;
  $export['nexteuropa_trackedchanges_tracking_status'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nexteuropa_trackedchanges_tracking_wbm_states';
  $strongarm->value = array(
    'validated' => 'validated',
    'published' => 'published',
  );
  $export['nexteuropa_trackedchanges_tracking_wbm_states'] = $strongarm;

  return $export;
}
