<?php

/**
 * @file
 * multisite_business_indicators_community.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_business_indicators_community_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function multisite_business_indicators_community_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
