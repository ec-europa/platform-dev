<?php

/**
 * @file
 * Reviews for the module's exported user permissions.
 */

/**
 * Performs automated review of the given module's exported user permissions.
 *
 * @param MultisiteReviewModule $module
 *   The machine name of the module to review.
 *
 * @return array
 *   An array of failures.
 */
function multisite_review_check_exported_user_permissions(MultisiteReviewModule $module) {
  module_load_include('inc', 'features', 'features.export');
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  // A list of permissions that should not be exported.
  $permission_blacklist = array(
    'administer features',
    'administer modules',
    'administer software updates',
    'manage features',
  );

  // A list of modules that should not have any of their permissions exported.
  $module_blacklist = array(
    'devel',
    'php',
  );

  // Only perform the review if the module is a feature.
  if (!$module->isFeature()) {
    return array();
  }

  // Check if the feature exports user permissions. Skip the review if it
  // doesn't.
  $info = features_get_modules($module->getName())->info;
  if (empty($info['features']['user_permission'])) {
    return array();
  }

  $failures = array();

  if ($defaults = features_get_default('user_permission', $module->getName())) {
    foreach ($defaults as $permission => $default) {
      // Check if any of the blacklisted permissions are exported.
      if (in_array($permission, $permission_blacklist)) {
        $failures[] = t('The blacklisted %permission permission is exported.', array(
          '%permission' => $permission,
        ));
      }

      // Check if the permission is related to a blacklisted module.
      if (in_array($default['module'], $module_blacklist)) {
        $failures[] = t('The %permission permission from the blacklisted module %module is exported.', array(
          '%permission' => $permission,
          '%module' => $default['module'],
        ));
      }
    }
  }
  else {
    // If the feature has listed user permissions in its info file but the
    // defaults could not be read then the feature was not exported correctly.
    $failures[] = t('The module %module exports user permissions but the defaults could not be read. The feature is not exported correctly.', array(
      '%module' => $module->getName(),
    ));
  }

  return $failures;
}
