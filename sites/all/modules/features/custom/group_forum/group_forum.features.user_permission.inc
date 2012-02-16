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

  return $permissions;
}
