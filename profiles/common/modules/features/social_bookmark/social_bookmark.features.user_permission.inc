<?php
/**
 * @file
 * social_bookmark.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function social_bookmark_user_default_permissions() {
  $permissions = array();

  // Exported permission: access social bookmark config page.
  $permissions['access social bookmark config page'] = array(
    'name' => 'access social bookmark config page',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'social_bookmark',
  );

  return $permissions;
}
