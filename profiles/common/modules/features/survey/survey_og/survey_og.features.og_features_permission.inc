<?php
/**
 * @file
 * survey_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function survey_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:create webform content'.
  $permissions['node:community:create webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete any webform content'.
  $permissions['node:community:delete any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own webform content'.
  $permissions['node:community:delete own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update any webform content'.
  $permissions['node:community:update any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own webform content'.
  $permissions['node:community:update own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
