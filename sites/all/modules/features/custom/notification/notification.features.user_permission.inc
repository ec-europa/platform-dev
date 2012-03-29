<?php
/**
 * @file
 * notification.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function notification_user_default_permissions() {
  $permissions = array();

  // Exported permission: create subscriptions
  $permissions['create subscriptions'] = array(
    'name' => 'create subscriptions',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'notifications',
  );

  // Exported permission: maintain own subscriptions
  $permissions['maintain own subscriptions'] = array(
    'name' => 'maintain own subscriptions',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'notifications',
  );

  // Exported permission: skip notifications
  $permissions['skip notifications'] = array(
    'name' => 'skip notifications',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'notifications',
  );

  // Exported permission: subscribe to content
  $permissions['subscribe to content'] = array(
    'name' => 'subscribe to content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'notifications_content',
  );

  return $permissions;
}
