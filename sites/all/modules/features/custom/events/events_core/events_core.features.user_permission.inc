<?php
/**
 * @file
 * events.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function events_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: create event content
  $permissions['create event content'] = array(
    'name' => 'create event content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any event content
  $permissions['delete any event content'] = array(
    'name' => 'delete any event content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own event content
  $permissions['delete own event content'] = array(
    'name' => 'delete own event content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any event content
  $permissions['edit any event content'] = array(
    'name' => 'edit any event content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own event content
  $permissions['edit own event content'] = array(
    'name' => 'edit own event content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );
 

  // custom permissions

  // Add permissions to roles ----------------------------------------------------------------------------------------------------------------------------------------------
  // Administrator
  $adm_rid = get_rid('administrator');  
  user_role_grant_permissions($adm_rid, array_keys(module_invoke_all('permission')));
  user_role_revoke_permissions($adm_rid, array(
    'administer modules',
  ));  

  user_role_revoke_permissions($adm_rid, array(
    'administer modules',
    'administer features',	
  )); 


  return $permissions;
}
