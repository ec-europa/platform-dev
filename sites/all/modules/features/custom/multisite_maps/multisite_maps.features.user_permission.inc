<?php
/**
 * @file
 * multisite_maps.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_maps_user_default_permissions() {
  $permissions = array();

  // Exported permission: create map content.
  $permissions['create map content'] = array(
    'name' => 'create map content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any map content.
  $permissions['delete any map content'] = array(
    'name' => 'delete any map content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own map content.
  $permissions['delete own map content'] = array(
    'name' => 'delete own map content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any map content.
  $permissions['edit any map content'] = array(
    'name' => 'edit any map content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own map content.
  $permissions['edit own map content'] = array(
    'name' => 'edit own map content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
