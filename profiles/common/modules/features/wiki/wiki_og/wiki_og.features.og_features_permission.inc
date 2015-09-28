<?php
/**
 * @file
 * wiki_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function wiki_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create wiki content'.
  $permissions['node:community:create wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any wiki content'.
  $permissions['node:community:delete any wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own wiki content'.
  $permissions['node:community:delete own wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any wiki content'.
  $permissions['node:community:update any wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own wiki content'.
  $permissions['node:community:update own wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
