<?php
/**
 * @file
 * Views implementation.
 */

/**
 * Implements hook_views_plugins().
 */
function nexteuropa_core_views_views_plugins() {
  return array(
    'row' => array(
      'nexteuropa_core_views_plugin_row_component_view' => array(
        'title' => t('Europa theme component'),
        'help' => t('Choose fields to display in the Europa theme component.'),
        'handler' => 'nexteuropa_core_views_plugin_row_component_view',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'style' => array(
      'nexteuropa_core_views_plugin_style_component_grid_view' => array(
        'title' => t('Europa Grid style component'),
        'help' => t('Choose the style component.'),
        'handler' => 'nexteuropa_core_views_plugin_style_component_grid_view',
        'uses fields' => FALSE,
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'theme' => 'grid',
      ),
    ),
  );
}
