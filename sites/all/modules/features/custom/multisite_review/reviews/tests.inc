<?php

/**
 * @file
 * Checks if tests are present.
 */

/**
 * Performs automated review of test presence.
 *
 * @param MultisiteReviewModule $module
 *   The machine name of the module to review.
 *
 * @return array
 *   An array of failures.
 */
function multisite_review_check_tests(MultisiteReviewModule $module) {
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  $failures = array();

  $path = DRUPAL_ROOT . '/' . $module->getPath();

  // Check if the module has a 'tests' folder.
  if (!file_exists($path . '/tests')) {
    $failures[] = t('The "/tests" folder is missing.');
  }

  // Check if the tests folder contains at least one test.
  if (!glob($path . '/tests/*.test')) {
    $failures[] = t('There are no files matching the pattern "*.test" in the "/tests" folder.');
  }

  return $failures;
}
