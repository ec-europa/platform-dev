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

  $menu_links['menu-service-tools:http://ec.europa.eu/contact/index_en.htm'] = array(
    'menu_name' => 'menu-service-tools',
    'link_path' => 'http://ec.europa.eu/contact/index_en.htm',
    'router_path' => '',
    'link_title' => 'Contact on Europa',
    'options' => array(
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
    'weight' => '-48',
  );

  $menu_links['menu-service-tools:http://ec.europa.eu/cookies/index_en.htm'] = array(
    'menu_name' => 'menu-service-tools',
    'link_path' => 'http://ec.europa.eu/cookies/index_en.htm',
    'router_path' => '',
    'link_title' => 'Cookies',
    'options' => array(
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
    'weight' => '-49',
  );

  $menu_links['menu-service-tools:http://ec.europa.eu/geninfo/legal_notices_en.htm'] = array(
    'menu_name' => 'menu-service-tools',
    'link_path' => 'http://ec.europa.eu/geninfo/legal_notices_en.htm',
    'router_path' => '',
    'link_title' => 'Legal notice',
    'options' => array(
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
    'weight' => '-50',
  );

  $menu_links['menu-service-tools:http://ec.europa.eu/geninfo/query/search_en.html'] = array(
    'menu_name' => 'menu-service-tools',
    'link_path' => 'http://ec.europa.eu/geninfo/query/search_en.html',
    'router_path' => '',
    'link_title' => 'Search on Europa',
    'options' => array(
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
    'weight' => '-47',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Contact on Europa');
  t('Cookies');
  t('European Commission');
  t('Legal notice');
  t('Search on Europa');
  t('[site:name]');

  return $menu_links;
}
