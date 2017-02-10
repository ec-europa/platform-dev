<?php
/**
 * @file
 * Contains Flexible Purge default Rules configuration.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function flexible_purge_default_rules_configuration() {
  $config = array();
  // Getting all Flexible Purge rules configuration files.
  $rules_path = drupal_get_path('module', 'flexible_purge') . '/rules';
  $files = file_scan_directory($rules_path, '/\.rule$/');
  foreach ($files as $file_path => $file) {
    require $file_path;

    if (isset($rule)) {
      $config[$file->name] = rules_import($rule);
    }
  }

  return $config;
}
