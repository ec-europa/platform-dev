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

  // Exported permission: administer media galleries
  $permissions['administer media galleries'] = array(
    'name' => 'administer media galleries',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'media_gallery',
  );

  // Exported permission: create media_gallery content
  $permissions['create media_gallery content'] = array(
    'name' => 'create media_gallery content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any media_gallery content
  $permissions['delete any media_gallery content'] = array(
    'name' => 'delete any media_gallery content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own media_gallery content
  $permissions['delete own media_gallery content'] = array(
    'name' => 'delete own media_gallery content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any media_gallery content
  $permissions['edit any media_gallery content'] = array(
    'name' => 'edit any media_gallery content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own media_gallery content
  $permissions['edit own media_gallery content'] = array(
    'name' => 'edit own media_gallery content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: import media
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'media',
  );

  return $permissions;
}