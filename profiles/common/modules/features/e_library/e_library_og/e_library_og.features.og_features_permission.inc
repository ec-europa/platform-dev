<?php

/**
 * @file
 * e_library_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function e_library_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create document content'.
  $permissions['node:community:create document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any document content'.
  $permissions['node:community:delete any document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own document content'.
  $permissions['node:community:delete own document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any document content'.
  $permissions['node:community:update any document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own document content'.
  $permissions['node:community:update own document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
