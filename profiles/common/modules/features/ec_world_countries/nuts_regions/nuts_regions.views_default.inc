<?php
/**
 * @file
 * Nuts_regions views altering.
 */

/**
 * Implements hook_views_default_views().
 *
 * Actual views are stored in the views folder.
 */
function nuts_regions_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'nuts_regions') . '/views', '/.*\.view$/');
  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }
  return $views;
}
