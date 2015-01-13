<?php
/**
 * @file
 * idea_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function idea_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create idea content'.
  $permissions['create idea content'] = array(
    'name' => 'create idea content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any idea content'.
  $permissions['delete any idea content'] = array(
    'name' => 'delete any idea content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own idea content'.
  $permissions['delete own idea content'] = array(
    'name' => 'delete own idea content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any idea content'.
  $permissions['edit any idea content'] = array(
    'name' => 'edit any idea content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own idea content'.
  $permissions['edit own idea content'] = array(
    'name' => 'edit own idea content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
