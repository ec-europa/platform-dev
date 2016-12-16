<?php

/**
 * @file
 * API documentation for the Multisite Review module.
 */

/**
 * Provides a list of supported review callbacks.
 *
 * @return array
 *   An associative array, keyed on review machine name. Each value is an
 *   associative array with the following keys:
 *   - name: The human readable name of the review.
 *   - description: Optional description of the review.
 *   - callback: The name of the function that will perform the review. This
 *     function needs to return a list of failures, which is a simple array of
 *     error messages.
 *   - file: The file in which the callback function resides, relative to the
 *     Drupal root folder.
 */
function hook_multisite_review_reviews() {
  $path = drupal_get_path('module', 'mymodule');

  return array(
    'mymodule_readme' => array(
      'name' => t('README file'),
      'description' => t('Checks whether the module has a README file with some necessary information.'),
      'callback' => 'mymodule_review_readme',
      'file' => $path . '/reviews/readme.inc',
    ),
  );
}
