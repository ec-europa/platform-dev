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
    user_role_grant_permissions($adm_rid, array(  
      'edit own wiki content',
      'edit any wiki content',
      'delete own wiki content',
      'delete any wiki content',
      'create wiki content',
    ));
    
    // Contributor
    $contrib_rid = get_rid('contributor');
    user_role_grant_permissions($contrib_rid, array(
      'edit own wiki content',
      'edit any wiki content',
      'delete own wiki content',
      'delete any wiki content',
      'create wiki content',
    ));
          
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
