<?php

/**
 * @file
 * nexteuropa_subscriptions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function nexteuropa_subscriptions_user_default_roles() {
  $roles = array();

  // Exported role: subscriber.
  $roles['subscriber'] = (object) array(
    'name' => 'subscriber',
    'weight' => 5,
  );

  return $roles;
}
