<?php
/**
 * @file
 * quicktabsandaccordeon.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function quicktabsandaccordeon_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer quicktabs.
  $permissions['administer quicktabs'] = array(
    'name' => 'administer quicktabs',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'quicktabs',
  );

  return $permissions;
}
