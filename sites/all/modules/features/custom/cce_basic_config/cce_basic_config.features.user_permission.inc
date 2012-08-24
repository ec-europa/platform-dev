<?php
/**
 * @file
 * cce_basic_config.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cce_basic_config_user_default_permissions() {
  $permissions = array();

  // Exported permission: search content.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: use advanced search.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: use text format basic_html.
  $permissions['use text format basic_html'] = array(
    'name' => 'use text format basic_html',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
      3 => 'contributor',
      4 => 'editor',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
