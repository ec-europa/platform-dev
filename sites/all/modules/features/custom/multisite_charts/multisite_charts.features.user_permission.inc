<?php
/**
 * @file
 * multisite_charts.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_charts_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create chart content'.
  $permissions['create chart content'] = array(
    'name' => 'create chart content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any chart content'.
  $permissions['delete any chart content'] = array(
    'name' => 'delete any chart content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own chart content'.
  $permissions['delete own chart content'] = array(
    'name' => 'delete own chart content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any chart content'.
  $permissions['edit any chart content'] = array(
    'name' => 'edit any chart content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own chart content'.
  $permissions['edit own chart content'] = array(
    'name' => 'edit own chart content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
