<?php
/**
 * @file
 * events_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function events_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create event content'.
  $permissions['node:community:create event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any event content'.
  $permissions['node:community:delete any event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own event content'.
  $permissions['node:community:delete own event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any event content'.
  $permissions['node:community:update any event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own event content'.
  $permissions['node:community:update own event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
