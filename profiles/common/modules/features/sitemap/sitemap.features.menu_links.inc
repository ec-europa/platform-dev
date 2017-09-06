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

  // Exported menu link: navigation_site-map:sitemap.
  $menu_links['navigation_site-map:sitemap'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Site map',
    'options' => array(
      'attributes' => array(
        'title' => 'Display a site map with RSS feeds.',
      ),
      'identifier' => 'navigation_site-map:sitemap',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'language' => LANGUAGE_NONE,
    'menu_links_customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Site map');

  return $menu_links;
}
