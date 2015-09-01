<?php

/**
 * @file
 * Mapeditor maps views integration.
 */

/**
 * Define mapeditor views style.
 *
 * Implements hook_views_plugins().
 */
function mapeditor_views_views_plugins() {
  $plugins = array(
    'module' => 'mapeditor_views',
    'style' => array(
      'leaflet' => array(
        'title' => t('Mapeditor Map'),
        'help' => t('Displays a View as a EC map.'),
        'path' => drupal_get_path('module', 'mapeditor_views'),
        'handler' => 'mapeditor_views_plugin_style',
        'theme' => 'mapeditor-map',
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
  );

  return $plugins;
}
