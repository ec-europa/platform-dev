<?php

/**
 * @file
 * Review for module .info files.
 */

/**
 * Performs automated review of the given module's .info file.
 *
 * @param MultisiteReviewModule $module
 *   The machine name of the module to review.
 *
 * @return array
 *   An array of failures.
 */
function multisite_review_check_info_file(MultisiteReviewModule $module) {
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  // Define a list of required keys. These are all specified in the custom
  // feature development guidelines.
  // @see https://webgate.ec.europa.eu/fpfis/wikis/display/MULTISITE/Build+custom+features
  $required_keys = array(
    'core',
    'description',
    'name',
    'package',
    'version',
  );

  // Features also require a 'features' key which lists the components that are
  // exported in the feature.
  if ($module->isFeature()) {
    $required_keys[] = 'features';
  }

  $results = array();

  $info = $module->getInfo();
  $name = $module->getName();
  foreach ($required_keys as $key) {
    if (!array_key_exists($key, $info)) {
      $args = array(
        '%module' => $name,
        '%key' => $key,
        '%type' => $module->type,
      );
      $results[$key] = t("The %type's %key is not set in %module.info file.", $args);
    }
  }

  // If the module is a feature, check for some specific key/value pairs that
  // are required according to the guidelines:
  // - the minimum PHP version.
  // - the Features API version.
  if ($module->isFeature()) {
    $required_values = array();
    $required_values['php'] = MULTISITE_REVIEW_PHP_VERSION;
    $required_values['features']['features_api'][0] = MULTISITE_REVIEW_FEATURES_API_VERSION;

    if ($missing_values = drupal_array_diff_assoc_recursive($required_values, $info)) {
      $missing_keys = implode(', ', array_keys($missing_values));
      $results['missing_values'] = t('Missing required key/value pairs in the .info file: %keys', array('%keys' => $missing_keys));
    }
  }

  // Check if the module has at least one test.
  $has_tests = FALSE;
  if (array_key_exists('files', $info)) {
    foreach ($info['files'] as $file) {
      if (substr($file, -5) === '.test') {
        $has_tests = TRUE;
        break;
      }
    }
  }

  if (!$has_tests) {
    $results['tests_missing'] = t('There are no tests added to the files[] array.');
  }

  // Check that there are no dependencies on the 'php' and 'menu' modules.
  foreach (array('menu', 'php') as $dependency) {
    if (!empty($info['dependencies']) && in_array($dependency, $info['dependencies'])) {
      $results[] = t('The dependency on the %dependency module should be removed.', array(
        '%dependency' => $dependency,
      ));
    }
  }

  // Check that there is no "tags" taxonomy exported.
  if (!empty($info['features']['taxonomy']) && in_array('tags', $info['features']['taxonomy'])) {
    $results[] = t('The "tags" vocabulary should not be exported.');
  }

  return $results;
}
