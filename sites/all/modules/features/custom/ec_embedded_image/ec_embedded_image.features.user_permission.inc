<?php
/**
 * @file
 * ec_embedded_image.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ec_embedded_image_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'add media from remote sources'.
  $permissions['add media from remote sources'] = array(
    'name' => 'add media from remote sources',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'media_internet',
  );

  // Exported permission: 'configure flickr'.
  $permissions['configure flickr'] = array(
    'name' => 'configure flickr',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'media_flickr',
  );

  return $permissions;
}
