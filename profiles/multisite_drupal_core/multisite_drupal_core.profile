<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function multisite_drupal_core_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}
/**
 * Implements hook_menu_link_alter().
 *
 * Alter the system links My Account and Log out
 */
function multisite_drupal_core_menu_link_alter(&$item) {

  $link_path = $item['link_path'];

  $user_classes = variable_get('user_classes', 'btn btn-default btn-xs');
  switch ($link_path) {
    case 'user':
      $user_icon = variable_get('user_myaccount_data_image', 'user');
      //$item['options']['attributes']['target'] = '_blank';
      $item['options']['attributes']['class'] = $user_classes;
      $item['options']['attributes']['data-image'] = variable_get('user_myaccount_data_image', 'user');
      break;
    
    case 'user/logout':
      $user_icon = variable_get('user_logout_data_image', 'log-out');
      $item['options']['attributes']['class'] = $user_classes;
      $item['options']['attributes']['data-image'] = variable_get('user_logout_data_image', 'log-out');
      break;
    default:
      break;
  }
}
