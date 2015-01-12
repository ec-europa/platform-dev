<?php
/**
 * @file
 * multisite_wysiwyg.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_wysiwyg_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'ckeditor_link',
  );

  return $permissions;
}
