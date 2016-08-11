<?php

/**
 * @file
 * nexteuropa_newsroom.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nexteuropa_newsroom_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer newsroom advanced settings'.
  $permissions['administer newsroom advanced settings'] = array(
    'name' => 'administer newsroom advanced settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'nexteuropa_newsroom',
  );

  // Exported permission: 'administer newsroom settings'.
  $permissions['administer newsroom settings'] = array(
    'name' => 'administer newsroom settings',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'nexteuropa_newsroom',
  );

  // Exported permission: 'create newsroom_item content'.
  $permissions['create newsroom_item content'] = array(
    'name' => 'create newsroom_item content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any newsroom_item content'.
  $permissions['delete any newsroom_item content'] = array(
    'name' => 'delete any newsroom_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own newsroom_item content'.
  $permissions['delete own newsroom_item content'] = array(
    'name' => 'delete own newsroom_item content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any newsroom_item content'.
  $permissions['edit any newsroom_item content'] = array(
    'name' => 'edit any newsroom_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own newsroom_item content'.
  $permissions['edit own newsroom_item content'] = array(
    'name' => 'edit own newsroom_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
