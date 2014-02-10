<?php
/**
 * @file
 * cce_basic_config.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cce_basic_config_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-breadcrumb-menu:http://ec.europa.eu/index_en.htm
  $menu_links['menu-breadcrumb-menu:http://ec.europa.eu/index_en.htm'] = array(
    'menu_name' => 'menu-breadcrumb-menu',
    'link_path' => 'http://ec.europa.eu/index_en.htm',
    'router_path' => '',
    'link_title' => 'European Commission',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'data-display-title' => '1',
        'data-remove-class' => 1,
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '0',
  );
  // Exported menu link: menu-breadcrumb-menu:menutoken/52ebaf910f9d0
  $menu_links['menu-breadcrumb-menu:menutoken/52ebaf910f9d0'] = array(
    'menu_name' => 'menu-breadcrumb-menu',
    'link_path' => 'menutoken/52ebaf910f9d0',
    'router_path' => 'menutoken/%',
    'link_title' => '[site:name]',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'data-display-title' => '1',
        'data-remove-class' => 1,
      ),
      'menu_token_link_path' => '<front>',
      'menu_token_data' => array(),
      'menu_token_options' => array(
        'clear' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('European Commission');
  t('[site:name]');

  // Exported menu link: management:admin/config/search/apachesolr/settings/solr/facets
  $menu_links['management:admin/config/search/apachesolr/settings/solr/facets'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/search/apachesolr/settings/solr/facets',
    'router_path' => 'admin/config/search/apachesolr/settings/%/facets',
    'link_title' => 'SolR facets',
    'options' => array(
      'attributes' => array(
        'data-display-title' => '1',
        'title' => 'Configure SolR facets',
        'data-remove-class' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '0',
    'parent_path' => 'admin/config/search',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('SolR facets');

  return $menu_links;
}
