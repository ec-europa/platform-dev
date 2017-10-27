<?php

/**
 * @file
 * nexteuropa_trackedchanges.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function nexteuropa_trackedchanges_filter_default_formats() {
  $formats = array();

  // Exported format: Full HTML + Change tracking.
  $formats['full_html_track'] = (object) array(
    'format' => 'full_html_track',
    'name' => 'Full HTML + Change tracking',
    'cache' => 0,
    'status' => 1,
    'weight' => -9,
    'filters' => array(
      'filter_url' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'toolbox_sanitize' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_autop' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(),
      ),
      'media_filter' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_tokens' => array(
        'weight' => 20,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
