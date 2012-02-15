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
    
    // Contributor
    $contrib_rid = get_rid('contributor');
    user_role_grant_permissions($contrib_rid, array(
      'access own webform results',
      'access own webform submissions',
      'delete own webform content',
      'delete own webform submissions',
      'edit own webform content',
      'edit own webform submissions',
      'access all webform results',
      'edit all webform submissions',
    ));

    // authenticated user
    $au_rid = get_rid('authenticated user');
    user_role_grant_permissions($au_rid, array(
      'access all webform results',
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
