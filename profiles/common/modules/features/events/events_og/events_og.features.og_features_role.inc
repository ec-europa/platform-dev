<?php

/**
 * @file
 * events_og.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function events_og_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:community:community_manager'.
  $roles['node:community:community_manager'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'community',
    'name' => 'community_manager',
  );

  return $roles;
}
