<?php
/**
 * @file
 * survey.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function survey_user_default_permissions() {
  $permissions = array();

  // Exported permission: access all webform results
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'webform',
  );

  return $permissions;
}
