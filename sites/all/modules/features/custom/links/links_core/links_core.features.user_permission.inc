<?php
/**
 * @file
 * links.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function links_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: create links content
  $permissions['create links content'] = array(
    'name' => 'create links content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any links content
  $permissions['delete any links content'] = array(
    'name' => 'delete any links content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own links content
  $permissions['delete own links content'] = array(
    'name' => 'delete own links content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any links content
  $permissions['edit any links content'] = array(
    'name' => 'edit any links content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own links content
  $permissions['edit own links content'] = array(
    'name' => 'edit own links content',
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
    'administer features',	
	'manage features',
  )); 


  return $permissions;
}
