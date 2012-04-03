<?php
/**
 * @file
 * news.features.user_permission.inc
 */

 
/**
 * Implements hook_user_default_permissions().
 */
function feed_rss_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: access news feeds
  $permissions['access news feeds'] = array(
    'name' => 'access news feeds',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'aggregator',
  );

  // Exported permission: administer news feeds
  $permissions['administer news feeds'] = array(
    'name' => 'administer news feeds',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'aggregator',
  );


  return $permissions;
}
