<?php
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