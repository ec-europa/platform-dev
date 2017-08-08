<?php
/**
 * @file
 * multisite_forum_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_forum_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create discussion content'.
  $permissions['create discussion content'] = array(
    'name' => 'create discussion content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any discussion content'.
  $permissions['delete any discussion content'] = array(
    'name' => 'delete any discussion content',
    'roles' => array(
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own discussion content'.
  $permissions['delete own discussion content'] = array(
    'name' => 'delete own discussion content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any discussion content'.
  $permissions['edit any discussion content'] = array(
    'name' => 'edit any discussion content',
    'roles' => array(
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own discussion content'.
  $permissions['edit own discussion content'] = array(
    'name' => 'edit own discussion content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
