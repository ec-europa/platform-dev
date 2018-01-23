<?php

/**
 * @file
 * links_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function links_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create links content'.
  $permissions['node:community:create links content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any links content'.
  $permissions['node:community:delete any links content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own links content'.
  $permissions['node:community:delete own links content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any links content'.
  $permissions['node:community:update any links content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own links content'.
  $permissions['node:community:update own links content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
