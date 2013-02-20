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
      'administrator' => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: bypass conversion video.
  $permissions['bypass conversion video'] = array(
    'name' => 'bypass conversion video',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: convert on submission.
  $permissions['convert on submission'] = array(
    'name' => 'convert on submission',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: create gallerymedia content.
  $permissions['create gallerymedia content'] = array(
    'name' => 'create gallerymedia content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any gallerymedia content.
  $permissions['delete any gallerymedia content'] = array(
    'name' => 'delete any gallerymedia content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own gallerymedia content.
  $permissions['delete own gallerymedia content'] = array(
    'name' => 'delete own gallerymedia content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any gallerymedia content.
  $permissions['edit any gallerymedia content'] = array(
    'name' => 'edit any gallerymedia content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own gallerymedia content.
  $permissions['edit own gallerymedia content'] = array(
    'name' => 'edit own gallerymedia content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: import media.
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'editor' => 'editor',
    ),
    'module' => 'media',
  );

  // Exported permission: override player dimensions.
  $permissions['override player dimensions'] = array(
    'name' => 'override player dimensions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'video',
  );

  // Exported permission: re convert video.
  $permissions['re convert video'] = array(
    'name' => 're convert video',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'video',
  );

  // Exported permission: use default thumb.
  $permissions['use default thumb'] = array(
    'name' => 'use default thumb',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'video',
  );

  return $permissions;
}
