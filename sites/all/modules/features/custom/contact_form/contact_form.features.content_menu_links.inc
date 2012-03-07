<?php
/**
 * @file
 * contact_form.features.content_menu_links.inc
 */

/**
 * Implements hook_content_menu_links_defaults().
 */
function contact_form_content_menu_links_defaults() {
  $menu_links = array();

  // Exported menu link: main-menu:contact
  $menu_links['main-menu:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact support',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Contact support');


  return $menu_links;
}
