<?php
/**
 * @file
 * multisite_translations.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function multisite_translations_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management:manage-translate
  $menu_links['management:manage-translate'] = array(
    'menu_name' => 'management',
    'link_path' => 'manage-translate',
    'router_path' => 'manage-translate',
    'link_title' => 'Manage translations',
    'options' => array(
      'attributes' => array(
        'data-display-title' => '1',
        'data-remove-class' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '0',
    'parent_path' => 'admin/tmgmt',
  );
  // Exported menu link: management:translate
  $menu_links['management:translate'] = array(
    'menu_name' => 'management',
    'link_path' => 'translate',
    'router_path' => 'translate',
    'link_title' => 'Translate',
    'options' => array(
      'attributes' => array(
        'data-display-title' => '1',
        'data-remove-class' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '0',
    'parent_path' => 'admin/tmgmt',
  );
  // Exported menu link: user-menu:manage-translate
  $menu_links['user-menu:manage-translate'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'manage-translate',
    'router_path' => 'manage-translate',
    'link_title' => 'Manage translation tasks',
    'options' => array(),
    'module' => 'system',
    'hidden' => '1',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: user-menu:translate
  $menu_links['user-menu:translate'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'translate',
    'router_path' => 'translate',
    'link_title' => 'Translate',
    'options' => array(),
    'module' => 'system',
    'hidden' => '1',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Manage translation tasks');
  t('Manage translations');
  t('Translate');


  return $menu_links;
}
