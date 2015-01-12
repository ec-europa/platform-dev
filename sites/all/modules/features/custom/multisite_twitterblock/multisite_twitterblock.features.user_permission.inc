<?php
/**
 * @file
 * multisite_twitterblock.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_twitterblock_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer fpfis twitter feature'.
  $permissions['administer fpfis twitter feature'] = array(
    'name' => 'administer fpfis twitter feature',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'multisite_twitterblock',
  );

  // Exported permission: 'administer fpfis twitter widget'.
  $permissions['administer fpfis twitter widget'] = array(
    'name' => 'administer fpfis twitter widget',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'multisite_twitterblock',
  );

  // Exported permission: 'override fpfis twitter widget'.
  $permissions['override fpfis twitter widget'] = array(
    'name' => 'override fpfis twitter widget',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'multisite_twitterblock',
  );

  return $permissions;
}
