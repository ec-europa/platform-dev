<?php
/**
 * @file
 * dev.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function dev_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: devel.
  $menus['devel'] = array(
    'menu_name' => 'devel',
    'title' => 'Development',
    'description' => 'Development link',
    'language' => 'und',
    'i18n_mode' => '0',
  );
  // Exported menu: management.
  $menus['management'] = array(
    'menu_name' => 'management',
    'title' => 'Management',
    'description' => 'The <em>Management</em> menu contains links for administrative tasks.',
    'language' => 'und',
    'i18n_mode' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Development');
  t('Development link');
  t('Management');
  t('The <em>Management</em> menu contains links for administrative tasks.');


  return $menus;
}
