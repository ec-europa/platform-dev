<?php
/**
 * @file
 * e_library_og.features.og_permission.inc
 */


// Add permissions to OG roles ---------------------------------------------------------------
    // Community Manager
    $cm_rid = get_og_rid('community_manager');
    og_role_grant_permissions($cm_rid, array(
      'create document content',
      'update own document content',
      'update any document content',
      'delete own document content',
      'delete any document content',
    ));
    
    // Administrator Member
    $admm_rid = get_og_rid('administrator member');
    og_role_grant_permissions($admm_rid, array(
      'create document content',
      'update own document content',
      'update any document content',
      'delete own document content',
      'delete any document content',
    ));
  
    // Member
    $mbr = get_og_rid('member');
    og_role_grant_permissions($mbr, array(
      'create document content',
      'update own document content',
      'delete own document content',
    ));