<?php

/**
 * @file
 * Reviews for the module's icon.
 */

/**
 * Performs automated review of the given module's icon.
 *
 * @param MultisiteReviewModule $module
 *   The machine name of the module to review.
 *
 * @return array
 *   An array of failures.
 */
function multisite_review_check_icon(MultisiteReviewModule $module) {
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  $failures = array();

  // If the module is a feature, check that it has an icon with the expected
  // filename.
  if ($module->isFeature()) {
    $filename = $module->getName() . '_icon.png';
    if (!file_exists($module->getPath() . '/' . $filename)) {
      $failures[] = t('An icon with filename %filename is not present.', array(
        '%filename' => $filename,
      ));
    }
  }

  return $failures;
}
