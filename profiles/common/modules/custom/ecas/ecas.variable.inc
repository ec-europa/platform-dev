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
  $variables[ECAS_EMAIL_ERROR_MESSAGE] = array(
    'type' => 'text_format',
    'title' => t('Error message text in case of an missing e-mail address', array(), $options),
    'description' => t('Text supplying information about the error caused by the absence of the e-mail in the EU Login profile.'),
    'required' => TRUE,
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_EMAIL_ERROR_MESSAGE_FACEBOOK] = array(
    'type' => 'text_format',
    'title' => t('Error message text in case of an missing e-mail address when using Facebook', array(), $options),
    'description' => t('Alternative text supplying information about the error caused by the absence of the e-mail in the EU Login profile created from Facebook.'),
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_LOGIN_MESSAGE] = array(
    'type' => 'string',
    'title' => t('Login message', array(), $options),
    'default' => '',
    'description' => t('Status message shown to the user after login. Available placeholders: %ecas_username.'),
    'group' => 'ecas',
    'localize' => TRUE,
  );

  $variables[ECAS_WARNING_MESSAGE] = array(
    'type' => 'string',
    'title' => t('Warning page message', array(), $options),
    'default' => '',
    'description' => t('Message on the warning page when a blocked account user is trying to log in'),
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