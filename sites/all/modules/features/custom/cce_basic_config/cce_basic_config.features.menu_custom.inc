<?php
/**
 * @file
 * cce_basic_config.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cce_basic_config_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-breadcrumb-menu.
  $menus['menu-breadcrumb-menu'] = array(
    'menu_name' => 'menu-breadcrumb-menu',
    'title' => 'Breadcrumb menu',
    'description' => 'Items to be displayed before the automatic breadcrumb',
    'language' => 'und',
    'i18n_mode' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Breadcrumb menu');
  t('Items to be displayed before the automatic breadcrumb');


  return $menus;
}
