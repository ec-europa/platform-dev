<?php

/**
 * @file
 * Configuration settings for cookie consent module.
 *
 * Fetch, customize and save site preferences for the cookie consent module.
 */

/**
 * Form constructor for the Cookie Consent administration form.
 */
function multisite_cookie_consent_admin_settings() {
  $connection_info = variable_get('multisite_cookie_connection');
  // If there is a connection.
  if ($connection_info) {

    // Configuration for connecting to the service.
    $form['eucookie_consent'] = array(
      '#type' => 'fieldset',
      '#title' => t('eucookie consent settings'),
      '#suffix' => multisite_cookie_consent_indicators(),
    );

    // Link to external consent javascript, it can be overwritten.
    $form['eucookie_consent']['eucookie_consent_ec_consent_javascript'] = array(
      '#type' => 'textfield',
      '#title' => t('Consent JavaScript file'),
      '#description' => t('This file is required! If you store this file locally, you can overwrite this setting, otherwise leave as it is.'),
      '#required' => TRUE,
      '#default_value' => variable_get('eucookie_consent_ec_consent_javascript', 'http://ec.europa.eu/wel/cookie-consent/consent.js'),
    );

    // Link to external consent javascript, it can be overwritten.
    $form['eucookie_consent']['eucookie_consent_ec_consent_loggedin'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display banner for logged in?'),
      '#description' => t('By default the cookie consent banner will shown
        only for anonymous user but check if you want to display it also for logged in users.'),
      '#default_value' => variable_get('eucookie_consent_ec_consent_loggedin', '0'),
    );

    // Get cookie info and store it to the database
    // future to be replaced by entity remote api.
    $form['eucookie_consent']['eucookie_consent_purge'] = array(
      '#type' => 'checkbox',
      '#title' => t('Rebuild remote cookie information?'),
      '#description' => t('Updates and saves remote information in your database'),
    );

    // Cookie static template pages.
    $form['eucookie_consent']['eucookie_consent_statictext'] = array(
      '#type' => 'checkbox',
      '#title' => t('Rebuild notice template page information?'),
      '#description' => t('Retrieves latest static description for the cookie notice pages.'),
    );

    // Cron frequency for automatic synch.
    $form['eucookie_consent']['eucookie_consent_cron_interval'] = array(
      '#type' => 'select',
      '#title' => t('Set the frequency of automatic rebuilding of the cookie list and the cookie notice page'),
      '#default_value' => variable_get('eucookie_consent_cron_interval', 86400),
      '#options' => array(
        0 => t('Every cron run'),
        86400 => t('Once a day'),
        604800 => t('Once a week'),
      ),
      '#description' => t('How often should the cookie notice page and the cookie descriptions rebuild and synchronized with the remote storage.'),
    );

    // Submit button.
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    );

    return $form;
  }
  else {
    // Configuration for connecting to the service.
    $form['eucookie_consent'] = array(
      '#type' => 'fieldset',
      '#title' => t('Connection not found!'),
    );

    $create_connection = url('admin/structure/clients', array('absolute' => TRUE));
    drupal_set_message(t('Please create a connection %connection', array('%connection' => $create_connection)));
    return $form;
  }
}

/**
 * Form submit handler for multisite_cookie_consent_admin_settings().
 *
 * @see multisite_cookie_consent_admin_settings()
 */
function multisite_cookie_consent_admin_settings_submit(array $form, array &$form_state) {
  // Overwrite the pointer to the EC consent.js file.
  variable_set('eucookie_consent_ec_consent_javascript', $form_state['values']['eucookie_consent_ec_consent_javascript']);
  // Set variable if you want to display banner to logged in users.
  variable_set('eucookie_consent_ec_consent_loggedin', $form_state['values']['eucookie_consent_ec_consent_loggedin']);
  // Set variable for synch frequency.
  variable_set('eucookie_consent_cron_interval', $form_state['values']['eucookie_consent_cron_interval']);
  // Fetch data from remote services.
  if ($form_state['values']['eucookie_consent_purge'] == 1) {
    _multisite_cookie_consent_rebuild_registered_cookies();
  }
  // Fetch template pages.
  if ($form_state['values']['eucookie_consent_statictext'] == 1) {
    _multisite_cookie_consent_rebuild_static_text();
  }
}
