<?php
/**
 * @file
 * sitemap.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sitemap_user_default_permissions() {
  $permissions = array();

  // Exported permission: access site map
  $permissions['access site map'] = array(
    'name' => 'access site map',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'site_map',
  );

  // Exported permission: administer xmlsitemap
  $permissions['administer xmlsitemap'] = array(
    'name' => 'administer xmlsitemap',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'xmlsitemap',
  );

  return $permissions;
}
