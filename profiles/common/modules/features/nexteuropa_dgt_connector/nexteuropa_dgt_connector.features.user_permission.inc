<?php
/**
 * @file
 * nexteuropa_dgt_connector.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nexteuropa_dgt_connector_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'configure dgt connector'.
  $permissions['manage feature dgt connector'] = array(
    'name' => 'manage feature dgt connector',
    'roles' => array(
      'cem' => 'cem',
    ),
    'module' => 'tmgmt_poetry',
  );

  return $permissions;
}
