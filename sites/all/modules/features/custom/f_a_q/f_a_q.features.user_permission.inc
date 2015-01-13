<?php
/**
 * @file
 * f_a_q.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function f_a_q_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create f_a_q content'.
  $permissions['create f_a_q content'] = array(
    'name' => 'create f_a_q content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any f_a_q content'.
  $permissions['delete any f_a_q content'] = array(
    'name' => 'delete any f_a_q content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own f_a_q content'.
  $permissions['delete own f_a_q content'] = array(
    'name' => 'delete own f_a_q content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any f_a_q content'.
  $permissions['edit any f_a_q content'] = array(
    'name' => 'edit any f_a_q content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own f_a_q content'.
  $permissions['edit own f_a_q content'] = array(
    'name' => 'edit own f_a_q content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
