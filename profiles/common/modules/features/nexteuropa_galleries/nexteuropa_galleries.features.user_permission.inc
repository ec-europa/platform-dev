<?php
/**
 * @file
 * nexteuropa_galleries.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nexteuropa_galleries_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create nexteuropa_gallerymedia content'.
  $permissions['create nexteuropa_gallerymedia content'] = array(
    'name' => 'create nexteuropa_gallerymedia content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any nexteuropa_gallerymedia content'.
  $permissions['delete any nexteuropa_gallerymedia content'] = array(
    'name' => 'delete any nexteuropa_gallerymedia content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own nexteuropa_gallerymedia content'.
  $permissions['delete own nexteuropa_gallerymedia content'] = array(
    'name' => 'delete own nexteuropa_gallerymedia content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any nexteuropa_gallerymedia content'.
  $permissions['edit any nexteuropa_gallerymedia content'] = array(
    'name' => 'edit any nexteuropa_gallerymedia content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own nexteuropa_gallerymedia content'.
  $permissions['edit own nexteuropa_gallerymedia content'] = array(
    'name' => 'edit own nexteuropa_gallerymedia content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
