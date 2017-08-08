<?php
/**
 * @file
 * multisite_mediagallery_community.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function multisite_mediagallery_community_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create gallerymedia content'.
  $permissions['node:community:create gallerymedia content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any gallerymedia content'.
  $permissions['node:community:delete any gallerymedia content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own gallerymedia content'.
  $permissions['node:community:delete own gallerymedia content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any gallerymedia content'.
  $permissions['node:community:update any gallerymedia content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own gallerymedia content'.
  $permissions['node:community:update own gallerymedia content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
