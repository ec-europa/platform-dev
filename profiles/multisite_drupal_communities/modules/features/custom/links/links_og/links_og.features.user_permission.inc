<?php
/**
 * @file
 * links.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function links_og_user_default_permissions() {
  $permissions = array();

  // Add permissions to OG roles ---------------------------------------------------------------  
  include_once('links_og.features.og_permission.inc');
  
  
  return $permissions;
}
