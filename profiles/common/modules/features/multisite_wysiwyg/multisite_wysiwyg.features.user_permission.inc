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

  // Exported permission: 'administer media wysiwyg view mode'.
  $permissions['administer media wysiwyg view mode'] = array(
    'name' => 'administer media wysiwyg view mode',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'media_wysiwyg_view_mode',
  );

  // Exported permission: 'use media wysiwyg'.
  $permissions['use media wysiwyg'] = array(
    'name' => 'use media wysiwyg',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'media_wysiwyg',
  );

  return $permissions;
}
