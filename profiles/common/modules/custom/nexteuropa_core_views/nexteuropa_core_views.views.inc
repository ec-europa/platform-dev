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
      'views_europa_banner_plugin_rows' => array(
        'title' => t('Europa Banner'),
        'help' => t('Choose the fields to display in Europa Banner Style.'),
        'path' => $module_path . '/plugins/banner',
        'handler' => 'ViewsEuropaBannerPluginRows',
        'theme' => 'banner',
        'theme path' => $theme_path . '/templates/banner',
        'theme file' => 'banner.component.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'views_europa_timelines_plugin_rows' => array(
        'title' => t('Europa Timelines'),
        'help' => t('Choose the fields to display in Europa Timelines Style.'),
        'path' => $module_path . '/plugins/timelines',
        'handler' => 'ViewsEuropaTimelinesPluginRows',
        'theme' => 'timeline',
        'theme path' => $theme_path . '/templates/timelines',
        'theme file' => 'timelines.component.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
