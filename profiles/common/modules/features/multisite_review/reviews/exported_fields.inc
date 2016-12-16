<?php

/**
 * @file
 * Reviews for the module's exported fields.
 */

/**
 * Performs automated review of the given module's exported fields.
 *
 * @param MultisiteReviewModule $module
 *   The machine name of the module to review.
 *
 * @return array
 *   An array of failures.
 */
function multisite_review_check_exported_fields(MultisiteReviewModule $module) {
  module_load_include('inc', 'features', 'includes/features.field');
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  $failures = array();

  // Only perform the review if the module is a feature.
  if (!$module->isFeature()) {
    return array();
  }

  // Check if the feature exports fields. Skip the review if it doesn't.
  $info = features_get_modules($module->getName())->info;
  if (empty($info['features']['field'])) {
    return array();
  }

  foreach ($info['features']['field'] as $identifier) {
    $field_export = features_field_load($identifier);
    $field_name = $field_export['field_config']['field_name'];

    // Check if the field is locked.
    if (empty($field_export['field_config']['locked'])) {
      $failures[] = t('The %field field is not locked.', array('%field' => $field_name));
    }

    // If it is a date field, check that it is configured to use UNIX time.
    if ($field_export['field_config']['module'] == 'date' && $field_export['field_config']['type'] != 'datestamp') {
      $failures[] = t('The %field field does not use UNIX time.', array('%field' => $field_name));
    }
  }

  return $failures;
}
