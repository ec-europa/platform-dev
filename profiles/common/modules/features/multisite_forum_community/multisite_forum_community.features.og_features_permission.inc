<?php
/**
 * @file
 * multisite_forum_community.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function multisite_forum_community_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:access forum'.
  $permissions['node:community:access forum'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:community:create discussion content'.
  $permissions['node:community:create discussion content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any discussion content'.
  $permissions['node:community:delete any discussion content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own discussion content'.
  $permissions['node:community:delete own discussion content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:moderate forum'.
  $permissions['node:community:moderate forum'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update any discussion content'.
  $permissions['node:community:update any discussion content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own discussion content'.
  $permissions['node:community:update own discussion content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
