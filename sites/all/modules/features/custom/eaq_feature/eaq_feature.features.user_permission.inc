<?php
/**
 * @file
 * eaq_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function eaq_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: access ask a question.
  $permissions['access ask a question'] = array(
    'name' => 'access ask a question',
    'roles' => array(
      0 => 'administrator',
      1 => 'eurodesk administrator',
      2 => 'eurodesk employee',
      3 => 'eurodesk manager',
    ),
    'module' => 'eaq',
  );

  // Exported permission: access overlay.
  $permissions['access overlay'] = array(
    'name' => 'access overlay',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'overlay',
  );

  // Exported permission: administer ask a question.
  $permissions['administer ask a question'] = array(
    'name' => 'administer ask a question',
    'roles' => array(
      0 => 'administrator',
      1 => 'eurodesk administrator',
    ),
    'module' => 'eaq',
  );

  // Exported permission: administer ask a question reassign.
  $permissions['administer ask a question reassign'] = array(
    'name' => 'administer ask a question reassign',
    'roles' => array(
      0 => 'administrator',
      1 => 'eurodesk manager',
    ),
    'module' => 'eaq',
  );

  // Exported permission: administer ask a question rules.
  $permissions['administer ask a question rules'] = array(
    'name' => 'administer ask a question rules',
    'roles' => array(
      0 => 'administrator',
      1 => 'eurodesk administrator',
    ),
    'module' => 'eaq',
  );

  return $permissions;
}
