<?php
/**
 * @file
 * multisite_notifications_og.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_notifications_og_user_default_permissions() {
  $permissions = array();

  // Exported permission: og subscribe.
  $permissions['og subscribe'] = array(
    'name' => 'og subscribe',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'subscriptions_og',
  );

  return $permissions;
}
