<?php
/**
 * @file
 * links.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function links_user_default_permissions() {
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
  
     // Add permissions to OG roles ---------------------------------------------------------------  
    // Community Manager
    $cm_rid = get_og_rid('community_manager');
    og_role_grant_permissions($cm_rid, array(
      'create links content',
      'update own links content',
      'update any links content',
      'delete own links content',
      'delete any links content',
    ));
      
    // Administrator Member
    $admm_rid = get_og_rid('administrator member');
    og_role_grant_permissions($admm_rid, array(
      'create links content',
      'update own links content',
      'update any links content',
      'delete own links content',
      'delete any links content',
    ));
    
    // Member
    $mbr = get_og_rid('member');
    og_role_grant_permissions($mbr, array(
      'create links content',
      'update own links content',
      'delete own links content',
    ));
  
  
  
  

  return $permissions;
}
