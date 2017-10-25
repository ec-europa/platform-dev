<?php

/**
 * @file
 * nexteuropa_communities.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function nexteuropa_communities_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-community-menu_homepage:menutoken/578e01d6cc02a.
  $menu_links['menu-community-menu_homepage:menutoken/578e01d6cc02a'] = array(
    'menu_name' => 'menu-community-menu',
    'link_path' => 'menutoken/578e01d6cc02a',
    'router_path' => 'menutoken/%',
    'link_title' => 'Homepage',
    'options' => array(
      'menu_token_link_path' => 'node/[site:og-context--node:nid]',
      'menu_token_data' => array(
        'node' => array(
          'type' => 'node',
          'plugin' => 'node_context',
          'options' => array(),
        ),
      ),
      'menu_token_options' => array(
        'clear' => 0,
      ),
      'alter' => TRUE,
      'menu_token_link_uuid' => 'menutoken/578e01d6cc02a',
      'identifier' => 'menu-community-menu_homepage:menutoken/578e01d6cc02a',
      'attributes' => array(
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'data-remove-class' => 0,
      ),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Homepage');

  return $menu_links;
}
