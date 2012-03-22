<?php
/**
 * @file
 * mediagallery_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function mediagallery_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: create media_gallery content
  $permissions['create media_gallery content'] = array(
    'name' => 'create media_gallery content',
    'roles' => array(),
  );

  // Exported permission: delete any media_gallery content
  $permissions['delete any media_gallery content'] = array(
    'name' => 'delete any media_gallery content',
    'roles' => array(),
  );

  // Exported permission: delete own media_gallery content
  $permissions['delete own media_gallery content'] = array(
    'name' => 'delete own media_gallery content',
    'roles' => array(),
  );

  // Exported permission: edit any media_gallery content
  $permissions['edit any media_gallery content'] = array(
    'name' => 'edit any media_gallery content',
    'roles' => array(),
  );

  // Exported permission: edit own media_gallery content
  $permissions['edit own media_gallery content'] = array(
    'name' => 'edit own media_gallery content',
    'roles' => array(),
  );

  return $permissions;
}
