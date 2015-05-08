<?php
/**
 * @file
 * multisite_notifications_core.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function multisite_notifications_core_user_default_roles() {
  $roles = array();

  // Exported role: subscriber.
  $roles['subscriber'] = array(
    'name' => 'subscriber',
    'weight' => '5',
  );

  return $roles;
}
