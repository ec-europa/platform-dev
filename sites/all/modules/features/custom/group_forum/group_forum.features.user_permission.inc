<?php
/**
 * @file
 * group_forum.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function group_forum_user_default_permissions() {
  $permissions = array();

  // Exported permission: create forum_room content
  $permissions['create forum_room content'] = array(
    'name' => 'create forum_room content',
    'roles' => array(),
  );
  
  // We should call the function _group_forum_grant_roles();
  _group_forum_grant_roles();
  //include_once( 'group_forum.features.og_permission.inc' );

  return $permissions;
}
