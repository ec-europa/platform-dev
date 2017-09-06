<?php

/**
 * @file
 * Multisite_readspeaker.features.user_permission.inc.
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_readspeaker_user_default_permissions() {
  $permissions = array();

  $permissions['administer multisite_readspeaker'] = array(
    'name' => 'administer multisite_readspeaker',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_readspeaker',
  );

  $permissions['display multisite_readspeaker'] = array(
    'name' => 'display multisite_readspeaker',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'multisite_readspeaker',
  );
  return $permissions;
}
