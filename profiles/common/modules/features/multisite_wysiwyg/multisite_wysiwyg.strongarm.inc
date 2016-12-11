<?php
/**
 * @file
 * multisite_wysiwyg.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function multisite_wysiwyg_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'multisite_wysiwyg';
  $strongarm->value = array(
    'change_tracking' => array(
      'action' => 'enable',
      'profile' => 'full_html',
    ),
    'dis_change_track_on_create' => 1,
    'en_change_track_on_edit' => 1,
  );
  $export['multisite_wysiwyg'] = $strongarm;

  return $export;
}
