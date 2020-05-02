<?php

/**
 * @file
 * Contains the constants used for connecting to the ECAS server.
 */

define('ECAS_MIN_PHPCAS_VERSION', "1.3.3");

$use_shared_fpfis = variable_get('ecas_use_shared_fpfis', FALSE);
if ($use_shared_fpfis) {
  // Point to the shared FPFIS library.
  if (!defined('FPFIS_COMMON_LIBRARIES_PATH')) {
    define('FPFIS_COMMON_LIBRARIES_PATH', '/home/fpfis/util/libraries');
  }

}
else {
  // Point to the local FPFIS library.
  if (!defined('FPFIS_COMMON_LIBRARIES_PATH')) {
    define('FPFIS_COMMON_LIBRARIES_PATH', drupal_get_path('module', 'ecas') . '/libraries');
  }
  if (!defined('FPFIS_SERVER_HOSTNAME')) {
    define('FPFIS_SERVER_HOSTNAME', '');
  }
  if (!defined('FPFIS_SERVER_PORT')) {
    define('FPFIS_SERVER_PORT', '');
  }
}

// Defines default values for various parameters.
define('ECAS_DEFAULT_ASSURANCE_LEVEL', 'LOW');
define('ECAS_DEFAULT_DOMAIN', '');
define('ECAS_DEFAULT_ACCOUNT_REQUEST_URL', 'https://ecas.ec.europa.eu/cas/eim/external/register.cgi?service=%local_ecas_url%');
define('ECAS_DEFAULT_CHANGE_PASSWORD_URL', 'https://ecas.ec.europa.eu/cas/init/passwordResetRequest.cgi');

define('ECAS_DEFAULT_DEBUG_LOGPATH', 'phpCas.log');

define('ECAS_DEFAULT_MAIL_ADDRESS', 'unknown.mail@nomail.nodomain.tld');

define('ECAS_DEFAULT_PROFILE_FIRSTNAME_FIELD', 'field_firstname');
define('ECAS_DEFAULT_PROFILE_LASTNAME_FIELD', 'field_lastname');
define('ECAS_DEFAULT_PROFILE_ECAS_MAIL_FIELD', 'field_ecas_mail');

define('ECAS_NO_LOGIN', 0);
define('ECAS_LOGIN', 1);
define('ECAS_GATEWAY', 2);

define('ECAS_DEFAULT_PAGES', '');
define('ECAS_LOGIN_EXLUDE_PAGES', 0);
define('ECAS_LOGIN_INCLUDE_PAGES', 1);

/**
  * ECAS group for CEM team users.
  */
define('ECAS_CEM_ECAS_GROUP', 'COMM_CEM');

/**
  * Name of the ecas login message variable.
  */
define('ECAS_LOGIN_MESSAGE', 'ecas_login_message');

/**
  * Name of the ecas login message variable.
  */
define('ECAS_WARNING_MESSAGE', 'ecas_warning_message');

/**
  * Name of the ecas no email variable message variable.
  */
define('ECAS_WARNING_MESSAGE_NO_EMAIL', 'ecas_no_email_message');

/**
  * Name of the ecas existing email message variable.
  */
define('ECAS_WARNING_MESSAGE_EXISTING_EMAIL', 'ecas_existing_mail_message');

/**
  * Name of the ecas not created message variable.
  */
define('ECAS_WARNING_MESSAGE_NOT_CREATED', 'ecas_not_created_message');

/**
  * Name of the ecas incomplete user message variable.
  */
define('ECAS_WARNING_MESSAGE_INCOMPLETE_USER', 'ecas_incomplete_user_message');

/**
 * Name of the ecas invalid strength message variable.
 */
define('ECAS_WARNING_MESSAGE_INVALID_STRENGTH', 'ecas_invalid_strength_message');

/**
  * Name of the ecas no email variable message variable.
  */
define('ECAS_WARNING_MESSAGE_SOCIAL', 'social_role_not_allowed_message');

/**
  * Ids for the different reasons causing a ECAS login failures.
  */
define('ECAS_WARNING_REASON_SOCIAL', 'social_role_not_allowed');
define('ECAS_WARNING_REASON_NO_EMAIL', 'no_mail');
define('ECAS_WARNING_REASON_EXISTING_EMAIL', 'mail_already_exists');
define('ECAS_WARNING_REASON_NOT_CREATED', 'not_created');
define('ECAS_WARNING_REASON_BLOCKED', 'account_blocked');
define('ECAS_WARNING_REASON_INCOMPLETE_USER', 'ecas_incomplete_user');
define('ECAS_WARNING_REASON_INVALID_STRENGTH', 'invalid_strength');
define('ECAS_WARNING_REASON_UNKNOWN', 'unknown');

/**
 * The full list of authentication methods for medium level of assurance is:
 * PASSWORD_SMS, PASSWORD_SOFTWARE_TOKEN, PASSWORD_MOBILE_APP, MOBILE_APP and MDM_CERT.
 * But it does not matter which of them we use for sending as strength.
 * It is enough to send one of these, to ensure the medium level of assurance will be used.
 * Also specifying others would not make any difference, since what is considered by EuLogin is
 * the level of the method, not the method itself.
 * The full list of authentication methods for medium level of assurance is:
 * PASSWORD_TOKEN,PASSWORD_TOKEN_CRAM, CLIENT_CERT.
 */
define('ECAS_ASSURANCE_LEVELS_STRENGTH_MEDIUM', 'MOBILE_APP');
define('ECAS_ASSURANCE_LEVELS_STRENGTH_HIGH', 'PASSWORD_TOKEN');
