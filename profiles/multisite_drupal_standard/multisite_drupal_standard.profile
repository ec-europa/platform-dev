<?php

/**
 * @file
 * Profile file of multisite drupal standards profile.
 */

// First attempt: sub-site on production.
if (conf_path() != 'sites/default' && file_exists(DRUPAL_ROOT . '/' . conf_path() . '/vendor/autoload.php')) {
  include_once DRUPAL_ROOT . '/' . conf_path() . '/vendor/autoload.php';
}
// Second attempt: sub-site in development.
elseif (file_exists(DRUPAL_ROOT . '/sites/all/vendor/autoload.php')) {
  include_once DRUPAL_ROOT . '/sites/all/vendor/autoload.php';
}
// Third attempt: Fallback to platform autoload.php, if any.
elseif (file_exists(DRUPAL_ROOT . '/vendor/autoload.php')) {
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
