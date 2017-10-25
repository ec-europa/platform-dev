<?php
/**
 * @file
 * communities.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function communities_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:community:View all unpublished content'.
  $permissions['node:community:View all unpublished content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:add user'.
  $permissions['node:community:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:administer group'.
  $permissions['node:community:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:approve and deny subscription'.
  $permissions['node:community:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:create article content'.
  $permissions['node:community:create article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:delete any article content'.
  $permissions['node:community:delete any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:delete own article content'.
  $permissions['node:community:delete own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:manage members'.
  $permissions['node:community:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:manage permissions'.
  $permissions['node:community:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:manage roles'.
  $permissions['node:community:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission:
  // 'node:community:moderate content from draft to needs_review'.
  $permissions['node:community:moderate content from draft to needs_review'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission:
  // 'node:community:moderate content from needs_review to draft'.
  $permissions['node:community:moderate content from needs_review to draft'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  // Exported og permission:
  // 'node:community:moderate content from needs_review to published'.
  $permissions['node:community:moderate content from needs_review to published'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission:
  // 'node:community:moderate content from needs_review to validated'.
  $permissions['node:community:moderate content from needs_review to validated'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission:
  // 'node:community:moderate content from published to archived'.
  $permissions['node:community:moderate content from published to archived'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission:
  // 'node:community:moderate content from validated to published'.
  $permissions['node:community:moderate content from validated to published'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:subscribe'.
  $permissions['node:community:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:community:subscribe without approval'.
  $permissions['node:community:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:community:unsubscribe'.
  $permissions['node:community:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:community:update any article content'.
  $permissions['node:community:update any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update group'.
  $permissions['node:community:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
    ),
  );

  // Exported og permission: 'node:community:update own article content'.
  $permissions['node:community:update own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'community_manager' => 'community_manager',
      'member' => 'member',
    ),
  );

  return $permissions;
}
