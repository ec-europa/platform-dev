<?php
/**
 * @file
 * nexteuropa_galleries.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function nexteuropa_galleries_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:editorial_team:create nexteuropa_gallerymedia content'
  $permissions['node:editorial_team:create nexteuropa_gallerymedia content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:editorial_team:delete any nexteuropa_gallerymedia content'
  $permissions['node:editorial_team:delete any nexteuropa_gallerymedia content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:editorial_team:delete own nexteuropa_gallerymedia content'
  $permissions['node:editorial_team:delete own nexteuropa_gallerymedia content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:editorial_team:update any nexteuropa_gallerymedia content'
  $permissions['node:editorial_team:update any nexteuropa_gallerymedia content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:editorial_team:update own nexteuropa_gallerymedia content'
  $permissions['node:editorial_team:update own nexteuropa_gallerymedia content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
