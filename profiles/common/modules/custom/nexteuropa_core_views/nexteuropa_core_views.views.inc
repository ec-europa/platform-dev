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
      'views_europa_component_plugin_rows' => array(
        'title' => t('Europa Component'),
        'help' => t('Choose the fields to display in Europa Component.'),
        'handler' => 'ViewsEuropaComponentPluginRows',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
