<?php
/**
 * @file
 * ec_embedded_video.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ec_embedded_video_user_default_permissions() {
  $permissions = array();

  // Exported permission: add media from remote sources.
  $permissions['add media from remote sources'] = array(
    'name' => 'add media from remote sources',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'media_internet',
  );

  return $permissions;
}
