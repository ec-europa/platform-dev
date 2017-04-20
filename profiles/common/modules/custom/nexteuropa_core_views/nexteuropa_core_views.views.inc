<?php
/**
 * @file
 * Views implementation.
 */

/**
 * Implements hook_views_plugins().
 */
function nexteuropa_core_views_views_plugins() {
  $module_path = drupal_get_path('module', 'nexteuropa_core_views');
  $theme_path = drupal_get_path('theme', 'europa');

  return array(
    'row' => array(
      'views_europa_card_plugin_rows' => array(
        'title' => t('Europa Card'),
        'help' => t('Choose the fields to display in Europa Card Style.'),
        'path' => $module_path . '/plugins/card',
        'handler' => 'ViewsEuropaCardPluginRows',
        'theme' => 'card',
        'theme path' => $theme_path . '/templates/card',
        'theme file' => 'card.component.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
