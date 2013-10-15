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

  // Exported permission: administer forums.
  $permissions['administer forums'] = array(
    'name' => 'administer forums',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'forum',
  );

  // Exported permission: create forum content.
  $permissions['create forum content'] = array(
    'name' => 'create forum content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any forum content.
  $permissions['delete any forum content'] = array(
    'name' => 'delete any forum content',
    'roles' => array(
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own forum content.
  $permissions['delete own forum content'] = array(
    'name' => 'delete own forum content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any forum content.
  $permissions['edit any forum content'] = array(
    'name' => 'edit any forum content',
    'roles' => array(
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own forum content.
  $permissions['edit own forum content'] = array(
    'name' => 'edit own forum content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
