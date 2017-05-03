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
        'title' => t('Europa Component'),
        'help' => t('Choose the fields to display in Europa Component.'),
        'handler' => 'nexteuropa_core_views_plugin_row_component_view',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
