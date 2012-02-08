<?php
/**
 * @file
 * wiki.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function wiki_user_default_permissions() {
  $permissions = array();

  // Exported permission: use text format wiki
  $permissions['use text format wiki'] = array(
    'name' => 'use text format wiki',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
