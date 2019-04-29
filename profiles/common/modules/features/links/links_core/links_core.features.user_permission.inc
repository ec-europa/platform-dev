<?php

/**
 * @file
 * links_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function links_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create links content'.
  $permissions['create links content'] = array(
    'name' => 'create links content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any links content'.
  $permissions['delete any links content'] = array(
    'name' => 'delete any links content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own links content'.
  $permissions['delete own links content'] = array(
    'name' => 'delete own links content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any links content'.
  $permissions['edit any links content'] = array(
    'name' => 'edit any links content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own links content'.
  $permissions['edit own links content'] = array(
    'name' => 'edit own links content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
