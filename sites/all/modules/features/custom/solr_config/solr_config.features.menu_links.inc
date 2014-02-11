<?php
/**
 * @file
 * solr_config.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function solr_config_menu_default_menu_links() {
  $menu_links = array();

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
    'weight' => '-44',
    'parent_path' => 'admin/config/search',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('SolR facets');


  return $menu_links;
}
