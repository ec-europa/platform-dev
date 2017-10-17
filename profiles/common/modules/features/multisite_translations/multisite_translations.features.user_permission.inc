<?php

/**
 * @file
 * multisite_translations.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_translations_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'accept translation jobs'.
  $permissions['accept translation jobs'] = array(
    'name' => 'accept translation jobs',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
      'translator' => 'translator',
      'translator_english' => 'translator_english',
    ),
    'module' => 'tmgmt',
  );

  // Exported permission: 'create translation jobs'.
  $permissions['create translation jobs'] = array(
    'name' => 'create translation jobs',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
      'translator_english' => 'translator_english',
    ),
    'module' => 'tmgmt',
  );

  // Exported permission: 'submit translation jobs'.
  $permissions['submit translation jobs'] = array(
    'name' => 'submit translation jobs',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
      'translator_english' => 'translator_english',
    ),
    'module' => 'tmgmt',
  );

  // Exported permission: 'translate content'.
  $permissions['translate content'] = array(
    'name' => 'translate content',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
      'translator_english' => 'translator_english',
    ),
    'module' => 'translation',
  );

  return $permissions;
}
