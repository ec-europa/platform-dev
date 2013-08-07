<?php
/**
 * @file
 * business_indicators.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function business_indicators_user_default_permissions() {
  $permissions = array();

  // Exported permission: access business indicators.
  $permissions['access business indicators'] = array(
    'name' => 'access business indicators',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'business_indicators',
  );

  return $permissions;
}
