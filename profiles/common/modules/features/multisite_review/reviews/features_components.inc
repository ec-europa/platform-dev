<?php

/**
 * @file
 * Reviews for the module's Features components.
 */

/**
 * Performs automated review of the given module's Features components.
 *
 * @param MultisiteReviewModule $module
 *   The machine name of the module to review.
 *
 * @return array
 *   An array of failures.
 */
function multisite_review_check_features_components(MultisiteReviewModule $module) {
  module_load_include('inc', 'features', 'features.export');
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  // A list of Features components that should not be exported.
  $components_blacklist = array(
    'menu_custom',
    'menu_links',
  );

  // Only perform the review if the module is a feature.
  if (!$module->isFeature()) {
    return array();
  }

  $failures = array();

  // Check if the feature exports any of the blacklisted components.
  $info = features_get_modules($module->getName())->info;
  if (!empty($info['features'])) {
    if ($components = array_intersect($components_blacklist, array_keys($info['features']))) {
      foreach ($components as $component) {
        $failures[] = t('The module exports the blacklisted component %component.', array(
          '%component' => $component,
        ));
      }
    }
  }

  return $failures;
}
