<?php
/**
 * @file
 * multisite_registration_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_registration_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer multisite_registration registration.
  $permissions['administer multisite_registration registration'] = array(
    'name' => 'administer multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: administer own multisite_registration registration.
  $permissions['administer own multisite_registration registration'] = array(
    'name' => 'administer own multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: administer registration.
  $permissions['administer registration'] = array(
    'name' => 'administer registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: administer registration states.
  $permissions['administer registration states'] = array(
    'name' => 'administer registration states',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: administer registration types.
  $permissions['administer registration types'] = array(
    'name' => 'administer registration types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: create multisite_registration registration.
  $permissions['create multisite_registration registration'] = array(
    'name' => 'create multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission:
  // create multisite_registration registration other anonymous.
  $permissions['create multisite_registration registration other anonymous'] = array(
    'name' => 'create multisite_registration registration other anonymous',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  // Exported permission:
  // create multisite_registration registration other users.
  $permissions['create multisite_registration registration other users'] = array(
    'name' => 'create multisite_registration registration other users',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  // Exported permission: delete any multisite_registration registration.
  $permissions['delete any multisite_registration registration'] = array(
    'name' => 'delete any multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: delete own multisite_registration registration.
  $permissions['delete own multisite_registration registration'] = array(
    'name' => 'delete own multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  // Exported permission: edit multisite_registration registration state.
  $permissions['edit multisite_registration registration state'] = array(
    'name' => 'edit multisite_registration registration state',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: update any multisite_registration registration.
  $permissions['update any multisite_registration registration'] = array(
    'name' => 'update any multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: update own multisite_registration registration.
  $permissions['update own multisite_registration registration'] = array(
    'name' => 'update own multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  // Exported permission: view multisite_registration registration.
  $permissions['view multisite_registration registration'] = array(
    'name' => 'view multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: view own multisite_registration registration.
  $permissions['view own multisite_registration registration'] = array(
    'name' => 'view own multisite_registration registration',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  return $permissions;
}
