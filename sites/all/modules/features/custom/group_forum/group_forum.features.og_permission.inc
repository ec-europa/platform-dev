<?php
/**
 * @file
 * group_forum.features.user_permission.inc
 */

// Add permissions associated to Room Management --------------------------------------------
// Administrator Member
$admm_rid = get_og_rid('administrator member');
og_role_grant_permissions($admm_rid, array(
  'create forum room content',
  'edit own forum room content',
  'delete own forum room content',
  'delete any forum room content',
));

// Community Manager
$cm_rid = get_og_rid('community_manager');
og_role_grant_permissions($cm_rid, array(
  'create forum room content',
  'edit own forum room content',
  'delete own forum room content',
  'delete any forum room content',
));

// Add permissions associated to Thread Management --------------------------------------------
// Administrator Member
$admm_rid = get_og_rid('administrator member');
og_role_grant_permissions($admm_rid, array(
  'create forum thread content',
  'edit own forum thread content',
  'delete own forum thread content',
  'delete any forum thread content',
));

// Community Manager
$cm_rid = get_og_rid('community_manager');
og_role_grant_permissions($cm_rid, array(
  'create forum thread content',
  'edit own forum thread content',
  'delete own forum thread content',
  'delete any forum thread content',
));

// Member
$contrib_rid = get_rid('member');
og_role_grant_permissions($contrib_rid, array(
  'edit own forum thread content',
  'delete own forum thread content',
  'create forum thread content',
));

