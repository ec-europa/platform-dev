<?php

/**
 * @file
 * Helpers for the install scripts.
 *
 */

/**
 * Get current module version.
 */
function _multisite_workbench_moderation_view_get_version() {
  $module = basename(__FILE__, ".install.inc");
  $path = drupal_get_path('module', $module) . '/' . $module . '.info';
  $info = drupal_parse_info_file($path);
  return $info['version'];
}

/**
 * Helper to remove view display.
 */
function _multisite_workbench_moderation_view_delete_display() {
  $view = views_get_view('workbench_moderation', TRUE);
  // Remove 'Moderate_all page' view displays menu tab
  if (isset($view->display['moderate_all_page']->display_options['menu']['type'])) {
    unset($view->display['moderate_all_page']->display_options['menu']['type']);
  }
  // Delete 'Moderate All' view display
  db_delete('views_display')
    ->condition('id', 'moderate_all_page')
    ->condition('vid', $view->vid)
    ->execute();

  // Empty cache now
  if (function_exists('views_invalidate_cache')) {
    views_invalidate_cache();
  }
}