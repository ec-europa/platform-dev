<?php
/**
 * @file
 * cce_basic_config.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function STARTERKIT_user_default_permissions() {
  $permissions = array();

  // Exported permission: access PDF version.
  $permissions['DEFINE YOUR PERMISSION'] = array(
    'name' => 'DEFINE YOUR PERMISSION',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'STARTERKIT',
  );






  return $permissions;
}
