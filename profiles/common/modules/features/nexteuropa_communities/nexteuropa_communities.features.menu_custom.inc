<?php

/**
 * @file
 * nexteuropa_communities.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function nexteuropa_communities_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-community-menu.
  $menus['menu-community-menu'] = array(
    'menu_name' => 'menu-community-menu',
    'title' => 'community',
    'description' => '',
    'language' => LANGUAGE_NONE,
    'i18n_mode' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('community');

  return $menus;
}
