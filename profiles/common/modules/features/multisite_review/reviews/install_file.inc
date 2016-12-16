<?php

/**
 * @file
 * Reviews for the module's .install file.
 */

/**
 * Performs automated review of the given module's .install file.
 *
 * @param MultisiteReviewModule $module
 *   The machine name of the module to review.
 *
 * @return array
 *   An array of failures.
 */
function multisite_review_check_install_file(MultisiteReviewModule $module) {
  module_load_include('inc', 'multisite_review', 'multisite_review_module');

  $failures = array();

  // Only review the install file if the module is a feature. Skip the test for
  // custom modules.
  if (!$module->isFeature()) {
    return array();
  }

  // Check if the module has an install file. Skip the rest of the review if it
  // is missing.
  $filename = $module->getPath() . '/' . $module->getName() . '.install';
  if (!file_exists($filename)) {
    $failures[] = t('No install file present.');
    return $failures;
  }

  // Load the install file.
  $install_file = file_get_contents($filename);

  // Check if the required hook implementations are present and documented
  // correctly.
  $required_hooks = array('enable', 'disable', 'install', 'uninstall');
  foreach ($required_hooks as $hook) {
    // Check if the hook implementation is present.
    preg_match('/^function ' . $module->getName() . '_' . $hook . '\(\) {$/m', $install_file, $matches);
    if (empty($matches[0])) {
      $failures[] = t('%hook is not implemented or its function declaration is not following the coding standards.', array(
        '%hook' => "hook_$hook()",
      ));
    }

    // Check if the hook is correctly documented.
    preg_match('/^\/\*\*\n \* Implements hook_' . $hook . '\(\).\n \*\/$/m', $install_file, $matches);
    if (empty($matches[0])) {
      $failures[] = t('The documentation for %hook is not present or is not following the coding standards.', array(
        '%hook' => "hook_$hook()",
      ));
    }
  }

  // Check if the enable and disable hooks output status messages.
  foreach (array('enable', 'disable') as $hook) {
    // This might throw false positives as it will just check if the text
    // 'drupal_set_message(' is present in between the function declaration and
    // a closing curly bracket at the beginning of a line. This will also match
    // cases where the call to drupal_set_message() is in a subsequent function.
    // If these false positives become a problem then the best way to fix this
    // is to use an actual PHP code parser such as nikic/PHP-Parser.
    preg_match('/^function ' . $module->getName() . '_' . $hook . '\(\) {\n.*drupal_set_message\(.*^}$/ms', $install_file, $matches);
    if (empty($matches[0])) {
      $failures[] = t('There is no call to drupal_set_message in %hook.', array(
        '%hook' => "hook_$hook()",
      ));
    }
  }

  return $failures;
}
