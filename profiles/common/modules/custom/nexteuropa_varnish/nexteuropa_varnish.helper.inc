<?php
/**
 * @file
 * File containing module's helper functions.
 */

/**
 * Gets Varnish settings to use in the purge process.
 *
 * @param bool $validity_control
 *   It indicates if the validity of the varnish settings must be also
 *   checked.
 *
 * @return array
 *   The Varnish settings:
 *    - 'varnish_request_method': HTTP request method use for Varnish requests;
 *    - 'varnish_http_targets': URLs of Varnish servers;
 *    - 'varnish_tag': Tag helping to identify site URLs in the Varnish index;
 *    - 'varnish_request_user': HTTP request user name for Varnish requests;
 *    - 'varnish_request_password': HTTP request password for Varnish requests;
 *    - 'varnish_http_timeout': HTTP request time out.
 *
 * @throws \InvalidArgumentException
 *   If $validity_control is set to true and one of the parameters is not set;
 *   I.E. all parameters must be set in order that the feature work correctly.
 */
function _nexteuropa_varnish_get_varnish_settings($validity_control = TRUE) {
  $settings = &drupal_static(__FUNCTION__);
  if (!$settings) {
    $settings['varnish_request_method'] = variable_get('nexteuropa_varnish_request_method');

    $variable = variable_get('nexteuropa_varnish_http_targets');
    // In case of "nexteuropa_varnish_http_targets" contains only one value, we
    // ensure that it is an array anyway.
    $settings['varnish_http_targets'] = (is_array($variable) || empty($variable)) ? $variable : array($variable);

    $settings['varnish_tag'] = variable_get('nexteuropa_varnish_tag');
    $settings['varnish_request_user'] = variable_get('nexteuropa_varnish_request_user');
    $settings['varnish_request_password'] = variable_get('nexteuropa_varnish_request_password');
    $settings['varnish_http_timeout'] = variable_get('nexteuropa_varnish_http_timeout');

    if ($validity_control && !(_nexteuropa_varnish_check_configuration($settings))) {
      throw new InvalidArgumentException(t('The module is not correctly set.'));
    }
  }
  return $settings;
}

/**
 * CHeck the module settings to see if they are correctly defined.
 *
 * @param array $settings
 *   The module settings to check.
 *
 * @return bool
 *   FALSE if at least one of the parameters is not correctly defined;
 *   otherwise TRUE.
 */
function _nexteuropa_varnish_check_configuration($settings) {
  if (empty($settings['varnish_request_method'])) {
    return FALSE;
  }

  if (empty($settings['varnish_http_targets'])) {
    return FALSE;
  }

  if (empty($settings['varnish_tag'])) {
    return FALSE;
  }

  if (empty($settings['varnish_request_user'])) {
    return FALSE;
  }

  if (empty($settings['varnish_request_password'])) {
    return FALSE;
  }

  if (empty($settings['varnish_http_timeout'])) {
    return FALSE;
  }

  return TRUE;
}
