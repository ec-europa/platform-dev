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

  // Exported permission: administer video presets.
  $permissions['administer video presets'] = array(
    'name' => 'administer video presets',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: bypass conversion video.
  $permissions['bypass conversion video'] = array(
    'name' => 'bypass conversion video',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: convert on submission.
  $permissions['convert on submission'] = array(
    'name' => 'convert on submission',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: create gallerymedia content.
  $permissions['create gallerymedia content'] = array(
    'name' => 'create gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
      2 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any gallerymedia content.
  $permissions['delete any gallerymedia content'] = array(
    'name' => 'delete any gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own gallerymedia content.
  $permissions['delete own gallerymedia content'] = array(
    'name' => 'delete own gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
      2 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any gallerymedia content.
  $permissions['edit any gallerymedia content'] = array(
    'name' => 'edit any gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own gallerymedia content.
  $permissions['edit own gallerymedia content'] = array(
    'name' => 'edit own gallerymedia content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
      2 => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: import media.
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
      2 => 'editor',
    ),
    'module' => 'media',
  );

  // Exported permission: override player dimensions.
  $permissions['override player dimensions'] = array(
    'name' => 'override player dimensions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: re convert video.
  $permissions['re convert video'] = array(
    'name' => 're convert video',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'video',
  );

  // Exported permission: use default thumb.
  $permissions['use default thumb'] = array(
    'name' => 'use default thumb',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'video',
  );

  return $permissions;
}
