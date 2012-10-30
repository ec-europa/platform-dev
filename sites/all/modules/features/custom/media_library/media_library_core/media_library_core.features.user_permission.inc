<?php
/**
 * @file
 * media_library_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function media_library_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: view file.
  $permissions['view file'] = array(
    'name' => 'view file',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  return $permissions;
}
