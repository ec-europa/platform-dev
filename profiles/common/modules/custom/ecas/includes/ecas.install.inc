<?php

/**
 * @file
 * Helper functions for module installation.
 */

/**
 * Set variables translatable if the i18n_variable module is enabled.
 */
function _ecas_set_variables_translatable() {
  if (!module_exists('i18n_variable')) {
    return;
  }

  $variable_realm_list_language = variable_get('variable_realm_list_language', array());
  $ecas_variables = array(
    ECAS_EMAIL_ERROR_MESSAGE,
    ECAS_EMAIL_ERROR_MESSAGE_SOCIAL,
    ECAS_LOGIN_MESSAGE,
    ECAS_WARNING_MESSAGE,
  );
  variable_set('variable_realm_list_language', array_merge($variable_realm_list_language, $ecas_variables));
}