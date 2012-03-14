<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function ideation_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:ideas/recent
  $menu_links['main-menu:ideas/recent'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'ideas/recent',
    'router_path' => 'ideas/recent',
    'link_title' => 'Ideas',
    'options' => array(
      'attributes' => array(
        'title' => 'Share, Discuss, and Vote on Ideas',
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
  t('Ideas');


  return $menu_links;
}
