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
  );
}
