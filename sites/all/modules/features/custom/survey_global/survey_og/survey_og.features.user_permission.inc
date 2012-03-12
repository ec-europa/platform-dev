<?php
/**
 * @file
 * survey.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function survey_og_user_default_permissions() {
  $permissions = array();

  // Add permissions to OG roles ---------------------------------------------------------------  
  // Community Manager
  $cm_rid = get_og_rid('community_manager');
  og_role_grant_permissions($cm_rid, array(
    'create webform content',
    'delete any webform content',
    'delete own webform content',
    'update any webform content',
    'update own webform content',
  ));

  $cmb_rid = get_og_rid('member');
  og_role_grant_permissions($cmb_rid, array(
    //'create webform content',
    //'delete own webform content',
    'update own webform content',
  ));

  // Administrator Member
  $admm_rid = get_og_rid('administrator member');
  og_role_grant_permissions($admm_rid, array(
    'create webform content',
    'delete any webform content',
    'delete own webform content',
    'update any webform content',
    'update own webform content',
  ));

  return $permissions;
}

