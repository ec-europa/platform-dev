<?php
/**
 * @file
 * wiki.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function wiki_og_user_default_permissions() {
  $permissions = array();

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
      'manage features',
      'show format selection for comment',
      'show format selection for file',
      'show format selection for node',
      'show format selection for rules_config',
      'show format selection for taxonomy_term',
      'show format selection for user',
      'show format tips',
      'show more format tips link',
      ));

  return $permissions;
}

