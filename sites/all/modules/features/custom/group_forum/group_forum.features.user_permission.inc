<?php
/**
 * @file
 * group_forum.features.user_permission.inc
 */

 
/**
 * Implements hook_user_default_permissions().
 */
function group_forum_user_default_permissions() {
  include_once('group_forum.features.og_permission.inc');
  return array();
}
