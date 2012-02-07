<?php
/**
 * @file
 * wiki.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function wiki_filter_default_formats() {
  $formats = array();

  // Exported format: wiki
  $formats['wiki'] = array(
    'format' => 'wiki',
    'name' => 'wiki',
    'cache' => '1',
    'status' => '1',
    'weight' => '0',
    'filters' => array(
      'filter_simplewiki' => array(
        'weight' => '0',
        'status' => '1',
        'settings' => array(
          'autotoc' => 0,
        ),
      ),
    ),
  );

  return $formats;
}
