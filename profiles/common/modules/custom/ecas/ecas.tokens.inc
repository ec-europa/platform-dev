<?php

/**
 * @file
 * Token module integration.
 */

/**
 * Implements hook_token_info().
 */
function ecas_token_info() {
  // Illustration related tokens.
  $info['types']['ecas-illustration'] = array(
    'name' => t('Ecas illustration images'),
    'description' => t('Tokens related to the default illustration images available for help and message texts.'),
    'needs-data' => 'ecas-illustration',
  );

  $info['tokens']['ecas-illustration']['fb-apps-settings-form'] = array(
    'name' => t('Facebook Apps & websites settings form.'),
    'description' => t('Full image HTML tag for the illustration of the Facebook Apps & websites settings form.'),
  );
  $info['tokens']['ecas-illustration']['fb-apps-settings-edit'] = array(
    'name' => t('Facebook Apps & websites settings edit form.'),
    'description' => t('Full image HTML tag for the illustration of the confirmation of a Facebook Apps & websites settings edit form.'),
  );
  $info['tokens']['ecas-illustration']['fb-apps-settings-confirm'] = array(
    'name' => t('Facebook Apps & websites settings confirmation.'),
    'description' => t('Full image HTML tag for the illustration of the confirmation of a Facebook Apps & websites settings submission.'),
  );
  $info['tokens']['ecas-illustration']['fb-apps-login-confirmation'] = array(
    'name' => t('Facebook Apps login confirmation.'),
    'description' => t('Full image HTML tag for the illustration of the confirmation popup allowing confirming the use of Facebook for the EU Login.'),
  );
  $info['tokens']['ecas-illustration']['fb-apps-login-settings-edit'] = array(
    'name' => t('Facebook Apps login settings edit.'),
    'description' => t('Full image HTML tag for the illustration of the Facebook form popup allowing edit the data provided to EU Login.'),
  );

  // URL related tokens.
  $info['types']['ecas-url'] = array(
    'name' => t('ECAS disclosable url'),
    'description' => t('Tokens related to the ECAS related URL that can be consulted by anonymous users.'),
    'needs-data' => 'ecas-url',
  );
  $info['tokens']['ecas-url']['account-request'] = array(
    'name' => t('URL of the EU Login account creation form'),
    'description' => t('URL for the EU Login account creation form.'),
  );
  $info['tokens']['ecas-url']['password-reset'] = array(
    'name' => t('URL of the EU Login password reset form'),
    'description' => t('URL for the EU Login account creation form.'),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function ecas_tokens($type, $tokens, array $data = array(), array $options = array()) {
  switch ($type) {
    case 'ecas-illustration':
      return _ecas_illustration_token($tokens);

    case 'ecas-url':
      return _ecas_url_token($tokens);
  }
}

/**
 * Profides replacement values for the 'ecas-illustration' placeholders type.
 *
 * @param array $tokens
 *   An array of tokens to be replaced.
 *
 * @return array
 *   An associative array of replacement values for the
 *   'ecas-illustration' placeholders.
 *
 * @see ecas_tokens()
 */
function _ecas_illustration_token(array $tokens) {
  $replacements = array();
  $module_img_repo = drupal_get_path('module', 'ecas') . '/tokens_images/';

  foreach ($tokens as $name => $original) {
    switch ($name) {
      case 'fb-apps-settings-form':
        $image_properties = array(
          'path' => $module_img_repo . 'fb_apps_websites_settings.png',
          'alt' => t('Illustration of the Facebook Apps & websites settings form.'),
          'width' => '50%',
        );
        break;

      case 'fb-apps-settings-confirm':
        $image_properties = array(
          'path' => $module_img_repo . 'fb_apps_websites_settings_confirm.png',
          'alt' => t('Illustration of the confirmation of a Facebook Apps & websites settings submission.'),
          'width' => '50%',
        );
        break;

      case 'fb-apps-settings-edit':
        $image_properties = array(
          'path' => $module_img_repo . 'fb_apps_websites_settings_edit.png',
          'alt' => t('Illustration of the confirmation of a Facebook Apps & websites settings edit form.'),
          'width' => '50%',
        );
        break;

      case 'fb-apps-login-confirmation':
        $image_properties = array(
          'path' => $module_img_repo . 'fb_authentication_screen.png',
          'alt' => t('Illustration of the confirmation popup allowing confirming the use of Facebook for the EU Login.'),
          'width' => '50%',
        );
        break;

      case 'fb-apps-login-settings-edit':
        $image_properties = array(
          'path' => $module_img_repo . 'fb_authentication_edit_form.png',
          'alt' => t('Illustration of the Facebook form popup allowing edit the data provided to EU Login.'),
          'width' => '50%',
        );
        break;
    }

    $replacements[$original] = theme('image', $image_properties);
  }

  return $replacements;
}

/**
 * Profides replacement values for the 'ecas-url' placeholders type.
 *
 * @param array $tokens
 *   An array of tokens to be replaced.
 *
 * @return array
 *   An associative array of replacement values for the
 *   'ecas-url' placeholders.
 *
 * @see ecas_tokens()
 */
function _ecas_url_token(array $tokens) {
  $replacements = array();

  foreach ($tokens as $name => $original) {
    switch ($name) {
      case 'account-request-url':
        $replacements[$original] = ecas_get_account_request_url();
        break;

      case 'account-request-link':
        $url = ecas_get_account_request_url();
        $replacements[$original] = l($url, $url);
        break;

      case 'password-reset-url':
        $replacements[$original] = variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL);
        break;

      case 'password-reset-link':
        $url = variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL);
        $replacements[$original] = l($url, $url);
        break;
    }
  }

  return $replacements;
}
