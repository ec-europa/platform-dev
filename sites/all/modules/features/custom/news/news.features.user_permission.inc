<?php
/**
 * @file
 * news.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function news_user_default_permissions() {
  $permissions = array();

  // Exported permission: create news content
  $permissions['create news content'] = array(
    'name' => 'create news content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any news content
  $permissions['delete any news content'] = array(
    'name' => 'delete any news content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own news content
  $permissions['delete own news content'] = array(
    'name' => 'delete own news content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any news content
  $permissions['edit any news content'] = array(
    'name' => 'edit any news content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own news content
  $permissions['edit own news content'] = array(
    'name' => 'edit own news content',
    'roles' => array(
      0 => 'administrator',
      1 => 'contributor',
    ),
    'module' => 'node',
  );
  
  
  
    
  //OG
  
      // Add permissions to roles ----------------------------------------------------------------------------------------------------------------------------------------------
    // Administrator
    $adm_rid = get_rid('administrator');
    user_role_grant_permissions($adm_rid, array(
      'edit own news content',
      'edit any news content',
      'delete own news content',
      'delete any news content',
      'create news content',
    ));
   
    // Contributor
    $ctb_rid = get_rid('contributor');      
    user_role_grant_permissions($ctb_rid, array(
      'edit own news content',
      'edit any news content',
      'delete own news content',
      'delete any news content',
      'create news content',
    ));
          
    // Add permissions to OG roles ---------------------------------------------------------------
    // Community Manager
    $cm_rid = get_og_rid('community_manager');
    og_role_grant_permissions($cm_rid, array(
      'create news content',
      'update own news content',
      'update any news content',
      'delete own news content',
      'delete any news content',
    ));
    
    // Administrator Member
    $admm_rid = get_og_rid('administrator member');
    og_role_grant_permissions($admm_rid, array(
      'create news content',
      'update own news content',
      'update any news content',
      'delete own news content',
      'delete any news content',
    ));
  
    // Member
    $mbr = get_og_rid('member');
    og_role_grant_permissions($mbr, array(
      'create news content',
      'update own news content',
      'delete own news content',
    ));

  return $permissions;
}
