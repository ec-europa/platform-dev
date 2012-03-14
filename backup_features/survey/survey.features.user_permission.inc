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



  // custom permissions
  // Add permissions to roles ----------------------------------------------------------------------------------------------------------------------------------------------
  // Administrator
  $adm_rid = get_rid('administrator');  
  user_role_grant_permissions($adm_rid, array_keys(module_invoke_all('permission')));
  user_role_revoke_permissions($adm_rid, array(
    'administer modules',
  ));  
          
  // Add permissions to OG roles ---------------------------------------------------------------  
  // Community Manager
  $cm_rid = get_og_rid('community_manager');
  og_role_grant_permissions($cm_rid, array(
    'create webform content',
    'delete any webform content',
    'delete own webform content',
    'update any webform content',
    'update own webform content',
  ));

  $cmb_rid = get_og_rid('member');
  og_role_grant_permissions($cmb_rid, array(
    //'create webform content',
    //'delete own webform content',
    'update own webform content',
  ));

  // Administrator Member
  $admm_rid = get_og_rid('administrator member');
  og_role_grant_permissions($admm_rid, array(
    'create webform content',
    'delete any webform content',
    'delete own webform content',
    'update any webform content',
    'update own webform content',
  ));

  return $permissions;
}
