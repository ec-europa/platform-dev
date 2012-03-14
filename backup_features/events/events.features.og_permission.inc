<?php
/**
 * @file
 * events.features.og_permission.inc
 */


// Add permissions to OG roles ---------------------------------------------------------------
    // Community Manager
    $cm_rid = get_og_rid('community_manager');
    og_role_grant_permissions($cm_rid, array(
      'create event content',
      'update own event content',
      'update any event content',
      'delete own event content',
      'delete any event content',
    ));
    
    // Administrator Member
    $admm_rid = get_og_rid('administrator member');
    og_role_grant_permissions($admm_rid, array(
      'create event content',
      'update own event content',
      'update any event content',
      'delete own event content',
      'delete any event content',
    ));
  
    // Member
    $mbr = get_og_rid('member');
    og_role_grant_permissions($mbr, array(
      'create event content',
      'update own event content',
      'delete own event content',
    ));