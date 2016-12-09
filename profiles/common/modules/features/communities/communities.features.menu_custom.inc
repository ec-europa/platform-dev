<?php

/**
 * @file
 * communities.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function communities_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-communities-menu.
  $menus['menu-communities-menu'] = array(
    'menu_name' => 'menu-communities-menu',
    'title' => 'Communities menu',
    'description' => 'Contextual menu for communities functions',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Communities menu');
  t('Contextual menu for communities functions');

  return $menus;
}
