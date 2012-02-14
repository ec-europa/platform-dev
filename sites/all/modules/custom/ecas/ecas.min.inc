<?php
// $Id$
/**
 * @file
 * This file embeds the base code of the ecas module, i.e. constants and
 * everything related to the admin forms.
 */

/* Defines default values for various parameters */
define('ECAS_DEFAULT_ASSURANCE_LEVEL', 'LOW');

define('ECAS_DEFAULT_ACCOUNT_REQUEST_URL', 'https://webgate.ec.europa.eu/aida/selfreg?service=%local_ecas_url%');
define('ECAS_DEFAULT_CHANGE_PASSWORD_URL', 'https://webgate.ec.europa.eu/cas/ec/change/changePassword.do');

define('ECAS_DEFAULT_DEBUG_LOGPATH', 'phpCas.log');

define('ECAS_DEFAULT_LOGIN_MESSAGE', 'Logged in via ECAS as %ecas_username.');
define('ECAS_DEFAULT_MAIL_ADDRESS', 'unknown.mail@address.net');

define('ECAS_PROFILE_DEFAULT_CATEGORY',        'user info');
define('ECAS_PROFILE_DEFAULT_FIRSTNAME_FIELD', 'firstname');
define('ECAS_PROFILE_DEFAULT_LASTNAME_FIELD',  'lastname');
define('ECAS_PROFILE_DEFAULT_ECAS_MAIL_FIELD', 'ecas_mail');

define ('ECAS_NO_LOGIN', 0);
define ('ECAS_LOGIN',    1);
define ('ECAS_GATEWAY',  2);

/**
 * Implementation of hook_help().
 */
function ecas_help($section) {
  switch ($section) {
    case 'admin/modules#description':
      return t('Allows users to authenticate via ECAS.');
  }
}

/**
 * Implementation of hook_perm().
 * @return array Permissions defined by the ecas module
 */
function ecas_perm() {
  return array('administer ecas');
}

/**
 * Implementation of hook_menu().
 */
function ecas_menu() {
  global $user;
  $items = array();

  $items['admin/settings/ecas'] = array(
    'title' => t('ECAS settings'),
    'description' => 'Configure ECAS',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ecas_admin_settings'),
    'access arguments' => array('administer ecas'),
    'type' => MENU_NORMAL_ITEM,
  );

  if (function_exists('_ecas_menu')) {
    _ecas_menu($items);
  }

  return $items;
}

/**
 * @param $user A user object
 * @return TRUE if the given user is an ECAS user, FALSE otherwose
 */
function _is_ecas_user($user) {
  if ($authmap_res = db_query('SELECT module FROM {authmap} WHERE uid = %d', $user->uid)) {
    if ($first_record = db_fetch_array($authmap_res)) {
      if ($first_record['module'] == 'ecas') {
        return (TRUE);
      }
    }
  }
  return (FALSE);
}

/**
 * Handle any form modification in this module.
 */
function ecas_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'user_profile_form') {
      if (_is_ecas_user($GLOBALS['user'])) {
        // remove the "Password", "Confirm password" ...
        $form['account']['pass']['#access'] = FALSE;
        // ... and "E-mail address" fields from the 'user/%/edit' page
        // $form['account']['mail']['#access'] = FALSE;
        $form['account']['mail']['#disabled'] = TRUE;

        $ecas_ch_pw_url = variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL);
        $form['account']['ecas_information_label'] = array(
          '#value' => sprintf(
            t('This account is managed by ECAS. Its password can be changed using %s.'),
            l('the ECAS change password page', $ecas_ch_pw_url)
          ),
        );
      }
  }
  elseif ($form_id == 'user_pass') {
    $form['#validate'] = array('_ecas_user_pass_validate');
  }
}


/**
 * Validate the user/password form: if the given user is an ECAS user,
 * provide an ECAS-related URL instead of sending a mail with erroneous
 * instructions.
 */
function _ecas_user_pass_validate($form, &$form_state) {
  $name = trim($form_state['values']['name']);

  // Try to load by email.
  $account = user_load(array('mail' => $name));
  if (!$account) {
    // No success, try to load by name.
    $account = user_load(array('name' => $name));
  }
  if ($account) {
    if (_is_ecas_user($account)) {
      $ecas_ch_pw_url = variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL);
      $ecas_ch_pw_link = l($ecas_ch_pw_url, $ecas_ch_pw_url);
      $message = t('This user appears to be an ECAS user -- you can not recover his password using this form. Please visit %s instead');
      $displayed_message = sprintf($message, $ecas_ch_pw_link);
      form_set_error('name', $displayed_message);
      return;
    }
  }
  user_pass_validate($form, $form_state);
}

/**
 * @return the administration form for the ECAS module
 */
function ecas_admin_settings() {
  $form['param'] = array(
    '#type' => 'fieldset',
    '#title' => t('ECAS module settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['param']['ecas_assurance_level'] = array(
    '#type' => 'select',
    '#title' => t('ECAS Assurance Level for this application'),
    '#default_value' => variable_get('ecas_assurance_level', constant('ECAS_DEFAULT_ASSURANCE_LEVEL')),
    '#options' => _ecas_assurance_levels(),
    '#description' => t('The ECAS Assurance Level defines which kinds of users may log into the application.'),
  );

  $ecas_domains = array('' => 'Do not force the default domain');
  $ecas_domains += _ecas_domains();

  $form['param']['ecas_domain'] = array(
    '#type' => 'select',
    '#title' => t('Default ECAS domain'),
    '#default_value' => variable_get('ecas_domain', ''),
    '#options' => $ecas_domains,
    '#description' => t('This option specifies the default domain that will be displayed on the login page if none is specified in cookies sent by the browser.'),
  );

  $form['param']['ecas_account_request_url'] = array(
    '#type' => 'textfield',
    '#title' => t('ECAS Account Request URL'),
    '#default_value' => variable_get('ecas_account_request_url', ECAS_DEFAULT_ACCOUNT_REQUEST_URL),
    '#description' => t('URL used to redirect the user to the ECAS account request service. The %local_ecas_url% placeholder will be replaced by the absolute URL to /ecas.'),
  );
  $form['param']['ecas_change_password_url'] = array(
    '#type' => 'textfield',
    '#title' => t('ECAS Change Password URL'),
    '#default_value' => variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL),
    '#description' => t('URL given to an ECAS user when he tries to get his password back using the user/password page.'),
  );

  $form['param']['debug_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debug options'),
    '#collapsible' => TRUE,
    '#collapsed' => !variable_get('ecas_phpcas_debug', FALSE),
  );
  $form['param']['debug_fieldset']['ecas_phpcas_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable phpCas client debug mode.'),
    '#default_value' => variable_get('ecas_phpcas_debug', FALSE),
    '#description' => t('If this option is checked, the phpCAS client will log many informations for each login attempt in a given file.'),
  );
  $form['param']['debug_fieldset']['ecas_phpcas_debug_logpath'] = array(
    '#type' => 'textfield',
    '#title' => t('phpCas debug file path'),
    '#default_value' => variable_get('ecas_phpcas_debug_logpath', constant('ECAS_DEFAULT_DEBUG_LOGPATH')),
    '#description' => t('If the phpCas client debug mode is enabled, the debug informations will be stored into this file. Specify either an absolute path, or a path relative to the Drupal directory. Please ensure this file is writable by Drupal since this module does not check it.'),
  );

  $options = array('1' => t('Active'), '0' => t('Blocked'));
  $form['param']['ecas_account_option'] = array(
    '#type' => 'radios',
    '#title' => t('User account status (first login)'),
    '#default_value' => variable_get('ecas_account_option', 1),
    '#options' => $options,
    '#description' => t('Status of the user account after creation'),
  );

  // specific setting for the import_users module
  if (module_exists('import_users')) {
    $form['param']['import_users_default_status'] = array(
      '#type' => 'radios',
      '#title' => sprintf('%s (%s)', t('User account status'), l(t('admin import'), 'admin/user/user/import')),
      '#default_value' => variable_get('import_users_default_status', 1),
      '#options' => $options,
      '#description' => t('Status of the user account after import by an administrator'),
    );
  }

  $form['param']['ecas_login_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Login message'),
    '#default_value' => variable_get('ecas_login_message', ECAS_DEFAULT_LOGIN_MESSAGE),
    '#description' => t('Status message shown to the user after login. Available placeholders: %ecas_username'),
  );
  $form['param']['ecas_warning_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Warning page message'),
    '#default_value' => variable_get('ecas_warning_message', t('Your account is not yet approved')),
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('Message on the warning page when a blocked account user is trying to log in'),
  );

  $form['param']['ecas_update_mail_address'] = array(
    '#type' => 'checkbox',
    '#title' => t('Update the user\'s mail address at login time.'),
    '#default_value' => variable_get('ecas_update_mail_address', TRUE),
    '#description' => t('If this option is checked, the ECAS module will replace the mail address of the user with the one retrieved from the ECAS/LDAP instance.'),
  );
  $form['param']['ecas_default_mail_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Default mail address'),
    '#default_value' => variable_get('ecas_default_mail_address', ECAS_DEFAULT_MAIL_ADDRESS),
    '#description' => t('This address will be assigned to the user if the previous option is disabled.'),
  );

  // specific settings regarding the integration with the profile module
  if (module_exists('profile')) {
    // checkbox to enable or disable the whole integration stuff
    $form['param']['ecas_profile_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable integration with the &quot;Profile&quot; module'),
      '#default_value' => variable_get('ecas_profile_enabled', FALSE),
      '#description' => t('If this option is checked, the ECAS module will attempt to fill the core profile of the user with informations retrieved from the ECAS/LDAP instance: first name, last name, mail address'),
    );

    $form['param']['profile_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Profile integration settings'),
      '#collapsible' => TRUE,
      '#collapsed' => !variable_get('ecas_profile_enabled', FALSE),
    );

    $form['param']['profile_fieldset']['ecas_profile_firstname_category'] = array(
      '#type' => 'textfield',
      '#title' => t('Firstname Profile category'),
      '#default_value' => variable_get('ecas_profile_firstname_category', ECAS_PROFILE_DEFAULT_CATEGORY),
      '#description' => t('Enter here the category of the Profile field that will be filled with the firstname retrieved from ECAS.'),
    );
    $form['param']['profile_fieldset']['ecas_profile_firstname_field'] = array(
      '#type' => 'textfield',
      '#title' => t('Firstname Profile field'),
      '#default_value' => variable_get('ecas_profile_firstname_field', ECAS_PROFILE_DEFAULT_FIRSTNAME_FIELD),
      '#description' => t('Enter here the title of the Profile field that will be filled with the firstname retrieved from ECAS. Leave empty if you do not want to retrieve it.'),
    );
    $form['param']['profile_fieldset']['ecas_profile_lastname_category'] = array(
      '#type' => 'textfield',
      '#title' => t('Lastname Profile category'),
      '#default_value' => variable_get('ecas_profile_lastname_category', ECAS_PROFILE_DEFAULT_CATEGORY),
      '#description' => t('Enter here the category of the Profile field that will be filled with the lastname retrieved from ECAS.'),
    );
    $form['param']['profile_fieldset']['ecas_profile_lastname_field'] = array(
      '#type' => 'textfield',
      '#title' => t('Lastname Profile field'),
      '#default_value' => variable_get('ecas_profile_lastname_field', ECAS_PROFILE_DEFAULT_LASTNAME_FIELD),
      '#description' => t('Enter here the title of the Profile field that will be filled with the lastname retrieved from ECAS. Leave empty if you do not want to retrieve it.'),
    );
    $form['param']['profile_fieldset']['ecas_profile_ecas_mail_category'] = array(
      '#type' => 'textfield',
      '#title' => t('ECAS Mail address Profile category'),
      '#default_value' => variable_get('ecas_profile_ecas_mail_category', ECAS_PROFILE_DEFAULT_CATEGORY),
      '#description' => t('Enter here the category of the Profile field that will be filled with the mail address retrieved from ECAS.'),
    );
    $form['param']['profile_fieldset']['ecas_profile_ecas_mail_field'] = array(
      '#type' => 'textfield',
      '#title' => t('ECAS Mail address Profile field'),
      '#default_value' => variable_get('ecas_profile_ecas_mail_field', ECAS_PROFILE_DEFAULT_ECAS_MAIL_FIELD),
      '#description' => t('Enter here the title of the Profile field that will be filled with the mail address retrieved from ECAS. Leave empty if you do not want to retrieve it.'),
    );

    $form['param']['profile_fieldset']['footnote'] = array(
      '#value' => '<p>' . t('Note: You can configure the Profile fields using ') . l(t('the Profile admin page'), 'admin/user/profile') . '.</p>',
    );
  }

  // specific settings regarding the integration with the content_profile module
  if (module_exists('content_profile')) {
    // checkbox to enable or disable the whole integration stuff
    $form['param']['ecas_content_profile_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable integration with the &quot;Content Profile&quot; module'),
      '#default_value' => variable_get('ecas_content_profile_enabled', FALSE),
      '#description' => t('If this option is checked, the ECAS module will attempt to fill the content profile of the user with informations retrieved from the ECAS/LDAP instance: first name, last name, mail address'),
    );

    $form['param']['content_profile_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content Profile integration settings'),
      '#collapsible' => TRUE,
      '#collapsed' => !variable_get('ecas_content_profile_enabled', FALSE),
    );

    /*
      in order to insert the informations into the content profile, we need
      two kinds of informations :
        - the name of the content type used as profile
        - the names of target fields in this content type
    */
    $form['param']['content_profile_fieldset']['ecas_content_profile_type'] = array(
      '#type' => 'textfield',
      '#title' => t('Content type to use'),
      '#default_value' => variable_get('ecas_content_profile_type', 'profile'),
      '#description' => t('This content type will be used to create the user profile.'),
    );

    $form['param']['content_profile_fieldset']['ecas_content_profile_firstname_field'] = array(
      '#type' => 'textfield',
      '#title' => t('First name field'),
      '#default_value' => variable_get('ecas_content_profile_firstname_field', 'field_firstname'),
      '#description' => t('This field will be used to store the first name of the user. Leave empty if you do not want to retrieve it.'),
    );
    $form['param']['content_profile_fieldset']['ecas_content_profile_lastname_field'] = array(
      '#type' => 'textfield',
      '#title' => t('Last name field'),
      '#default_value' => variable_get('ecas_content_profile_lastname_field', 'field_lastname'),
      '#description' => t('This field will be used to store the last name of the user. Leave empty if you do not want to retrieve it.'),
    );
    $form['param']['content_profile_fieldset']['ecas_content_profile_mail_field'] = array(
      '#type' => 'textfield',
      '#title' => t('ECAS mail field'),
      '#default_value' => variable_get('ecas_content_profile_mail_field', 'field_ecas_mail'),
      '#description' => t('This field will be used to store the mail of the user, as known by ECAS. Leave empty if you do not want to retrieve it. Note that the field is expected to be of type &quot;Mail&quot;, not &quot;textfield&quot;'),
    );

    $form['param']['content_profile_fieldset']['footnote'] = array(
      '#value' => '<p>' . t('Note: You can configure the Content types using ') . l(t('the Content types list'), 'admin/content/types/list') . '.</p>',
    );
  }

  // checkbox dedicated to the 'group_sync' module, developed by the FPFIS team
  if (module_exists('group_sync')) {
    // checkbox to enable or disable the whole integration stuff
    $form['param']['ecas_group_sync_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable integration with the &quot;FPFIS Group Sync&quot; module'),
      '#default_value' => variable_get('ecas_group_sync_enabled', FALSE),
      '#description' => t('If this option is checked, the ECAS module will trigger the FPFIS Group Sync module to sync the user.'),
    );
  }

  return system_settings_form($form);
}

/**
 * @return array of assurance levels descriptions, keyed by assurance level
 */
function _ecas_assurance_levels() {
  $assurance_levels = array(
    'TOP'    => t('TOP: EC only'),
    'HIGH'   => t('HIGH: + Other institutions'),
    'MEDIUM' => t('MEDIUM: + Sponsored'),
    'LOW'    => t('LOW: + External + Self-registered'),
  );
  drupal_alter('ecas_assurance_levels', $assurance_levels);
  return $assurance_levels;
}

/**
 * @return the available ecas domains
 */
function _ecas_domains() {
  $known_ecas_domains = array(
    'eu.europa.ec'        => 'European Commission',
    'eu.europa.cdt'       => 'Translation Centre',
    'eu.europa.curia'     => 'Court of Justice of the European Union',
    'eu.europa.gsa'       => 'European GNSS Supervisory Authority',
    'eu.europa.eca'       => 'European Court of Auditors',
    'external'            => 'External',
    'eu.europa.consilium' => 'Council of the European Union',
    'eu.europa.eesc'      => 'European Economic and Social Committee',
    'eu.europa.cor'       => 'Committee of the Regions',
    'eu.europa.europarl'  => 'European Parliament',
  );
  drupal_alter('ecas_domains', $known_ecas_domains);
  return $known_ecas_domains;
}
