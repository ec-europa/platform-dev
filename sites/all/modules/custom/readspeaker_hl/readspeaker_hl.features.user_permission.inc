<?php
/**
 * @file
 * readspeaker.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function readspeaker_hl_user_default_permissions() {
  $permissions = array();

  $permissions['administer readspeaker_hl'] = array(
    'name' => 'administer readspeaker_hl',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'readspeaker_hl',
  );

  $permissions['display readspeaker_hl'] = array(
    'name' => 'display readspeaker_hl',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'readspeaker_hl',
  );
  return $permissions;
}
