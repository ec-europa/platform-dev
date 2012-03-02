<?php
/**
 * @file
 * sitemap.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sitemap_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:sitemap
  $menu_links['main-menu:sitemap'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'sitemap/all',
    'router_path' => 'sitemap',
    'link_title' => 'Site map',
    'options' => array(
      'attributes' => array(
        'title' => 'Display a site map with RSS feeds.',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10000',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Site map');


  return $menu_links;
}
