<?php

/**
 * @file
 * Helper functions for installing the feature Mega Menu.
 */

/**
 * Menu informations.
 *
 * Build the info array structure needed to create a megamenu instance
 * with the items in a normal menu (by default the main menu).
 *
 * @param string $mlid
 *   The normal menu id.
 *
 * @return mixed
 *   The menu info structure array or FALSE.
 */
function _multisite_megamenu_get_menu_info($mlid = 'main-menu') {
  if (!is_string($mlid)) {
    return FALSE;
  }
  $item_list = array($mlid);
  $result = db_query("SELECT mlid, plid, link_path, link_title, options, weight FROM {menu_links} WHERE hidden = 0 AND menu_name = :menu_name AND TRIM(link_title) > '' ORDER BY p1, p2, p3, p4, p5, p6, p7, p8, p9, plid, mlid, link_title ASC", array(':menu_name' => $mlid));
  while ($record = $result->fetchObject()) {
    $item_list[] = $record->mlid;
  }
  $items_str = ',' . implode(',', $item_list);
  $menu_info = array(
    $mlid => array(
      'mlid' => $mlid,
      'menu_list' => $items_str,
    ),
  );
  return $menu_info;
}

/**
 * Menu id.
 *
 * Get the id of a megamenu that has been created
 * by importing a normal menu (by default the main menu).
 *
 * @param string $mlid
 *   The normal menu id.
 *
 * @return mixed
 *   The megamenu id or FALSE.
 */
function _multisite_megamenu_get_imported_menu($mlid = 'main-menu') {
  // Load om_maximenu settings and look for the id of our new menu.
  $_om_maximenu_variable = variable_get('om_maximenu');
  $menu_id = FALSE;
  if (is_array($_om_maximenu_variable) && count($_om_maximenu_variable)) {
    $code = $mlid . '-imported';
    foreach ($_om_maximenu_variable as $m_id => $menu_data) {
      if ($code == $menu_data['code']) {
        $menu_id = $m_id;
        // Ensure skin option is set to no_style.
        $_om_maximenu_variable[$m_id]['skin'] = 'no_style';
        variable_set('om_maximenu', $_om_maximenu_variable);
        break;
      }
    }
  }
  return $menu_id;
}

/**
 * Megamenu instance.
 *
 * Create a megamenu instance and populate with the (flattened) menu items
 * in a normal menu (by default the main menu).
 *
 * @param string $mlid
 *   The normal menu id.
 *
 * @return mixed
 *   The megamenu menu.
 */
function _multisite_megamenu_import_menu($mlid = 'main-menu') {
  // Obtain main menu info and prepare data for import.
  $form = $form_state = array();
  $form_state['values']['om_import']['menus'] = _multisite_megamenu_get_menu_info($mlid);

  // Initialization of global variable with om_maximenu settings needed.
  global $_om_maximenu_variable;
  $_om_maximenu_variable = variable_get('om_maximenu');

  // Import main menu (but note: the global variable is not updated).
  require_once drupal_get_path('module', 'om_maximenu') . '/inc/om_maximenu.import.inc';
  om_maximenu_import_submit($form, $form_state);

  // Load om_maximenu settings and look for the id of our new menu.
  return _multisite_megamenu_get_imported_menu($mlid);
}
