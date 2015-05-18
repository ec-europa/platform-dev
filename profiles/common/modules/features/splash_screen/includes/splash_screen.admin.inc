<?php
/**
 * @file
 * Module's admin forms.
 */

/**
 * General configuration form.
 */
function _splash_screen_settings_form() {
  $fieldset_general = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $fieldset_general['splash_screen_home_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Real home page'),
    '#description' => t('Enter the path of the real home page, without language suffix, domain, and trailing slash, i.e.: home'),
    '#default_value' => variable_get('splash_screen_home_page', ''),
  );

  // Formats the blacklisted languages array as a line separated list
  // before displaying them.
  $blacklist_arr = variable_get('splash_screen_blacklist', array());
  $blacklist = implode("\r\n", $blacklist_arr);

  $fieldset_general['splash_screen_blacklist'] = array(
    '#type' => 'textarea',
    '#title' => t('Languages blacklist'),
    '#description' => t('Enter a line separated list of languages that should not be displayed on splash screen. Languages should be displayed with 2 digit code, i.e.: fr'),
    '#default_value' => $blacklist,
  );

  $form = array();

  // Inserts the fieldset for grouping general settings fields.
  $form['splash_screen'] = $fieldset_general;

  // Adds buttons for processing the form.
  $form['buttons'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
  );

  // Specifies the callback function for processing the form submission.
  $form['#submit'] = array('_splash_screen_admin_submit');

  // Specifies the theme for the form.
  $form['#theme'] = 'system_settings_form';

  return $form;
}

/**
 * Process the submitting of the administration form of this module.
 */
function _splash_screen_admin_submit($form, &$form_state) {

  // Pre-process list of blacklisted languages.
  $blacklist = $form_state['values']['splash_screen_blacklist'];
  $blacklist = trim($blacklist);
  $blacklist = preg_replace('/\s+/', "\r\n", $blacklist);
  $blacklist_arr = ($blacklist === '' ? array() : preg_split('/\r*\n+/', $blacklist));

  // Updates the $form_state before passing it to the Drupal system.
  $form_state['values']['splash_screen_blacklist'] = $blacklist_arr;

  // Delegates persistence to the existing Drupal system.
  system_settings_form_submit($form, $form_state);
}
