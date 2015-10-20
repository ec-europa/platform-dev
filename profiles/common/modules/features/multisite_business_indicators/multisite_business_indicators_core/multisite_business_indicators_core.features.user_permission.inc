<?php
/**
 * @file
 * multisite_business_indicators_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_business_indicators_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: access business indicators.
  $permissions['access business indicators'] = array(
    'name' => 'access business indicators',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_business_indicators_core',
  );

  return $permissions;
}
