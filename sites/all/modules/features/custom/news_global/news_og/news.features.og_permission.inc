<?php
          
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
