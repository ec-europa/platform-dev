<?php

/**
 * @file
 * Helper functions for the NextEuropa webtools install feature.
 */

/**
 * Implements hook_post_features_enable_feature().
 */
function nexteuropa_webtools_post_features_enable_feature($component) {
  // Grant webtools bean permissions for Administrator roles.
  $admin_rid = user_role_load_by_name('administrator');
  if ($admin_rid && isset($admin_rid->rid)) {
    user_role_grant_permissions($admin_rid->rid, array(
      'create any webtools bean',
      'edit any webtools bean',
      'view any webtools bean',
      'delete any webtools bean',
      'administer webtools',
    ));
  }
  // Grant webtools bean permissions for anonymous user role.
  user_role_grant_permissions('1', array(
    'view any webtools bean',
  ));
  // Grant webtools bean permissions for authenticated user role.
  user_role_grant_permissions('2', array(
    'view any webtools bean',
  ));
}
