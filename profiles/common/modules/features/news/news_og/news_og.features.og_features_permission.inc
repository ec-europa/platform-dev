<?php
/**
 * @file
 * news_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function news_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create news content'.
  $permissions['node:community:create news content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any news content'.
  $permissions['node:community:delete any news content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own news content'.
  $permissions['node:community:delete own news content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any news content'.
  $permissions['node:community:update any news content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own news content'.
  $permissions['node:community:update own news content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
