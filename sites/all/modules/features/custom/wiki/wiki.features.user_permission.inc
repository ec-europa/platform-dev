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

  // Add permissions to OG roles ---------------------------------------------------------------  
  // Community Manager
  $cm_rid = get_og_rid('community_manager');
  og_role_grant_permissions($cm_rid, array(
    'create wiki content',
    'update own wiki content',
    'update any wiki content',
    'delete own wiki content',
    'delete any wiki content',
  ));

  // Member
  $cmb_rid = get_og_rid('member');
  og_role_grant_permissions($cmb_rid, array(
    'create wiki content',
    'update own wiki content',
    'delete own wiki content',
    'update any wiki content',	
  ));

  // Administrator Member
  $admm_rid = get_og_rid('administrator member');
  og_role_grant_permissions($admm_rid, array(
    'create wiki content',
    'update own wiki content',
    'update any wiki content',
    'delete own wiki content',
    'delete any wiki content',
  ));

  return $permissions;
}
