<?php
/**
 * @file
 * f_a_q.features.content_menu_links.inc
 */

/**
 * Implements hook_content_menu_links_defaults().
 */
function f_a_q_content_menu_links_defaults() {
  $menu_links = array();

  // Exported menu link: main-menu:faq
  $menu_links['main-menu:faq'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'faq',
    'router_path' => 'faq',
    'link_title' => 'F.A.Q',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('F.A.Q');


  return $menu_links;
}
