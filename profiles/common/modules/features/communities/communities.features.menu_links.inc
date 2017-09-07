<?php

/**
 * @file
 * communities.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function communities_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: navigation:admin/workbench.
  $menu_links['navigation:admin/workbench'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/workbench',
    'router_path' => 'admin/workbench',
    'link_title' => 'My workbench',
    'options' => array(
      'attributes' => array(
        'title' => 'link to the workbench',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('My workbench');

  return $menu_links;
}
