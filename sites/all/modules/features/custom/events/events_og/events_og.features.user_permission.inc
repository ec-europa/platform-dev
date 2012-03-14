<?php
/**
 * @file
 * events.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function events_og_user_default_permissions() {
  $permissions = array();

  include_once('events_og.features.og_permission.inc');  
  
  return $permissions;
}
