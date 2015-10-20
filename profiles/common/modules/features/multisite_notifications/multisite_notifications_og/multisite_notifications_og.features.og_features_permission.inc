<?php
/**
 * @file
 * multisite_notifications_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function multisite_notifications_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:og subscribe'.
  $permissions['node:community:og subscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  return $permissions;
}
