<?php

/**
 * @file
 * Definition of module's variables for Variable API module.
 */

/**
 * Implements hook_variable_info().
 */
function ecas_variable_info($options) {
  $variables = array();
  $variables[ECAS_WARNING_MESSAGE_NO_EMAIL] = array(
    'type' => 'text_format',
    'title' => t('Error message text in case of an missing e-mail address', array(), $options),
    'default' => _ecas_get_default_warning_message(ECAS_WARNING_MESSAGE_NO_EMAIL),
    'description' => t('Text supplying information about the error caused by the absence of the e-mail in the EU Login profile.'),
    'required' => TRUE,
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_WARNING_MESSAGE_EXISTING_EMAIL] = array(
    'type' => 'text_format',
    'title' => t('Error message text in case of an e-mail address already used', array(), $options),
    'default' => _ecas_get_default_warning_message(ECAS_WARNING_MESSAGE_EXISTING_EMAIL),
    'description' => t('Text supplying information about the error caused by the an e-mail in the EU Login profile used in another.'),
    'required' => TRUE,
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_WARNING_MESSAGE_NOT_CREATED] = array(
    'type' => 'text_format',
    'title' => t('Error message text in case of an drupal user is not created', array(), $options),
    'default' => _ecas_get_default_warning_message(ECAS_WARNING_MESSAGE_NOT_CREATED),
    'description' => t('Text supplying information about the error caused by the non-creation of Drupal user from an EU Login profile.'),
    'required' => TRUE,
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_WARNING_MESSAGE_INCOMPLETE_USER] = array(
    'type' => 'text_format',
    'title' => t('Error message text in case of an ecas user is incomplete', array(), $options),
    'default' => _ecas_get_default_warning_message(ECAS_WARNING_MESSAGE_INCOMPLETE_USER),
    'description' => t(
      'Text supplying information about the error because the EU Login profile does not contain the required data, other then the email.'
    ),
    'required' => TRUE,
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_LOGIN_MESSAGE] = array(
    'type' => 'string',
    'title' => t('Login message', array(), $options),
    'default' => _ecas_get_default_login_message(),
    'description' => t('Status message shown to the user after login. Available placeholders: %ecas_username.'),
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_WARNING_MESSAGE] = array(
    'type' => 'text_format',
    'title' => t('Warning page message', array(), $options),
    'default' => _ecas_get_default_warning_message(ECAS_WARNING_MESSAGE),
    'description' => t('Message on the warning page when a blocked account user is trying to log in'),
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_WARNING_MESSAGE_SOCIAL] = array(
    'type' => 'text_format',
    'title' => t('Error message text in case of social login', array(), $options),
    'default' => _ecas_get_default_warning_message(ECAS_WARNING_MESSAGE_SOCIAL),
    'description' => t('Warning when a user with more then authenticated role is trying to log in with social media login.'),
    'group' => 'ecas',
    'localize' => TRUE,
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function ecas_variable_group_info() {
  $groups['ecas'] = array(
    'title' => t('Ecas'),
    'description' => t('Configure tracking behavior to get insights into your website traffic and marketing effectiveness.'),
    'access' => 'administer piwik',
    'path' => array('admin/config/ecas/settings'),
  );

  return $groups;
}
