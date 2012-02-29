<?php
/**
 * @file
 * wiki.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function wiki_user_default_permissions() {
  $permissions = array();

  // Exported permission: create wiki content
  $permissions['create wiki content'] = array(
    'name' => 'create wiki content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own wiki content
  $permissions['delete own wiki content'] = array(
    'name' => 'delete own wiki content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own wiki content
  $permissions['edit own wiki content'] = array(
    'name' => 'edit own wiki content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'contributor',
    ),
    'module' => 'node',
  );
  
  // Exported permission: use text format wiki
  $permissions['use text format wiki'] = array(
    'name' => 'use text format wiki',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'filter',
  );




  // custom permissions

  // Add permissions to roles ----------------------------------------------------------------------------------------------------------------------------------------------
  // Administrator
  $adm_rid = get_rid('administrator');  
  user_role_grant_permissions($adm_rid, array_keys(module_invoke_all('permission')));
  user_role_revoke_permissions($adm_rid, array(
    'administer modules',
  ));


  return $permissions;
}
