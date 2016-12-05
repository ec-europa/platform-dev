<?php
/**
 * @file
 * nexteuropa_trackedchanges.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nexteuropa_trackedchanges_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format full_html_track'.
  $permissions['use text format full_html_track'] = array(
    'name' => 'use text format full_html_track',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html_track'.
  $permissions['ckeditor_lite highlight changes'] = array(
    'name' => 'ckeditor_lite highlight changes',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
