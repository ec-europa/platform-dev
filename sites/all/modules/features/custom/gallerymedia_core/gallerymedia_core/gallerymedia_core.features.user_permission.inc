<?php
/**
 * @file
 * gallerymedia_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gallerymedia_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: create gallerymedia content.
  $permissions['create gallerymedia content'] = array(
    'name' => 'create gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any gallerymedia content.
  $permissions['delete any gallerymedia content'] = array(
    'name' => 'delete any gallerymedia content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own gallerymedia content.
  $permissions['delete own gallerymedia content'] = array(
    'name' => 'delete own gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any gallerymedia content.
  $permissions['edit any gallerymedia content'] = array(
    'name' => 'edit any gallerymedia content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own gallerymedia content.
  $permissions['edit own gallerymedia content'] = array(
    'name' => 'edit own gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );
  
    // Exported permission: import media.
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
