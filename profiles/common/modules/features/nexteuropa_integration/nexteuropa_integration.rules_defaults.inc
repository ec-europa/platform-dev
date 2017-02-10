<?php
/**
 * @file
 * Contains NextEuropa Integration default Rules configuration.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function nexteuropa_integration_default_rules_configuration() {
  $config = array();
  // Getting all NextEuropa Integration rules configuration files.
  $rules_path = drupal_get_path('module', 'nexteuropa_integration') . '/rules';
  $files = file_scan_directory($rules_path, '/\.rule$/');
  foreach ($files as $file_path => $file) {
    require $file_path;

    if (isset($rule)) {
      $config[$file->name] = rules_import($rule);
    }
  }

  return $config;
}
