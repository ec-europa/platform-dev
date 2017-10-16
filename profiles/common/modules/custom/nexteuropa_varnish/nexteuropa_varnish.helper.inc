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
 *    - 'varnish_request_method': HTTP request method used for Varnish requests;
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
    $variable_items_names = _nexteuropa_varnish_get_settings_item_names();

    foreach ($variable_items_names as $param_name => $var_item_name) {
      $value = variable_get($param_name);

      // In case of "nexteuropa_varnish_http_targets" contains only one value,
      // we ensure that it is an array anyway.
      if (($param_name == 'nexteuropa_varnish_http_targets') && (!empty($value) && !is_array($value))) {
        $value = array($value);
      }
      $settings[$var_item_name] = $value;
    }

    if ($validity_control && !(_nexteuropa_varnish_check_configuration($settings))) {
      throw new InvalidArgumentException(t('The module is not correctly set.'));
    }
  }
  return $settings;
}

/**
 * Check the module settings to see if they are correctly defined.
 *
 * @param array $settings
 *   The module settings to check.
 *
 * @return bool
 *   FALSE if at least one of the parameters is not correctly defined;
 *   otherwise TRUE.
 */
function _nexteuropa_varnish_check_configuration($settings) {
  $all_configurations = _nexteuropa_varnish_get_settings_item_names();
  foreach ($all_configurations as $configuration) {
    if (empty($settings[$configuration])) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Gets the key names used in the module settings array.
 *
 * @return array
 *   The key names of settings array. The array is keyed by the actual variable
 *   name as defined the "settings.php" file.
 */
function _nexteuropa_varnish_get_settings_item_names() {
  return array(
    'nexteuropa_varnish_request_method' => 'varnish_request_method',
    'nexteuropa_varnish_http_targets' => 'varnish_http_targets',
    'nexteuropa_varnish_tag' => 'varnish_tag',
    'nexteuropa_varnish_request_user' => 'varnish_request_user',
    'nexteuropa_varnish_request_password' => 'varnish_request_password',
    'nexteuropa_varnish_http_timeout' => 'varnish_http_timeout',
  );
}
