<?php
/**
 * @file
 * group_forum.features.og_permission.inc
 */

// Add permissions associated to Room Management --------------------------------------------
// Administrator Member
$admm_rid = get_og_rid('administrator member');
og_role_grant_permissions($admm_rid, array(
  'create forum_room content',
  'update own forum_room content',
  'delete own forum_room content',
  'delete any forum_room content',
));

// Community Manager
$cm_rid = get_og_rid('community_manager');
og_role_grant_permissions($cm_rid, array(
  'create forum_room content',
  'update own forum_room content',
  'delete own forum_room content',
  'delete any forum_room content',
));

// Add permissions associated to Thread Management --------------------------------------------
// Administrator Member
$admm_rid = get_og_rid('administrator member');
og_role_grant_permissions($admm_rid, array(
  'create forum_thread content',
  'update own forum_thread content',
  'delete own forum_thread content',
  'delete any forum_thread content',
));

// Community Manager
$cm_rid = get_og_rid('community_manager');
og_role_grant_permissions($cm_rid, array(
  'create forum_thread content',
  'update own forum_thread content',
  'delete own forum_thread content',
  'delete any forum_thread content',
));

// Member
$contrib_rid = get_rid('member');
og_role_grant_permissions($contrib_rid, array(
  'update own forum_thread content',
  'delete own forum_thread content',
  'create forum_thread content',
));

