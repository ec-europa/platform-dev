<?php

/**
 * @file
 * Taxonomy Browser Features integration.
 */

/**
 * Implements hook_views_api().
 */
function taxonomy_browser_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
