<?php
/**
 * @file
 * Profile file of multisite drupal standards profile.
 */

if (file_exists(DRUPAL_ROOT . '/vendor/autoload.php')) {
  include_once DRUPAL_ROOT . '/vendor/autoload.php';
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function multisite_drupal_standard_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}
