<?php

/**
 * @file
 * media_avportal/includes/media_avportal.variables.inc
 *
 * Variable defaults for Media: AV Portal.
 */

/**
 * Define our constants.
 */

/**
 * This is the variable namespace, automatically prepended to module variables.
 */
define('MEDIA_AVPORTAL_NAMESPACE', 'media_avportal__');

/**
 * This is the rest point for the AV Portal api.
 *
 * Avoid using the gdata api url when possible. Too many calls will result in
 * throttling and 403 errors.
 */
define('MEDIA_AVPORTAL_REST_API', 'https://gdata.avportal.com/feeds/api/videos');

/**
 * Variable system uses Ctools Exportables.
 */

/**
 * Wrapper for variable_get() using the Media: AV Portal variable registry.
 */
function media_avportal_variable_get($name, $default = NULL) {
  // Allow for an override of the default. Useful when a variable is required
  // (like $path), but namespacing is still desired.
  if (!isset($default)) {
    $default = media_avportal_variable_default($name);
  }
  // Namespace all variables.
  $variable_name = MEDIA_AVPORTAL_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the Media: AV Portal variable registry.
 */
function media_avportal_variable_set($name, $value) {
  $variable_name = MEDIA_AVPORTAL_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the Media: AV Portal variable registry.
 */
function media_avportal_variable_del($name) {
  $variable_name = MEDIA_AVPORTAL_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Media: AV Portal namespace.
 */
function media_avportal_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'width' => 640,
      'height' => 390,
      'autohide' => 2,
      'autoplay' => FALSE,
      'color' => 'red',
      'enablejsapi' => FALSE,
      'loop' => FALSE,
      'modestbranding' => FALSE,
      'nocookie' => FALSE,
      'origin' => '',
      'protocol' => 'https:',
      'protocol_specify' => FALSE,
      'rel' => TRUE,
      'showinfo' => TRUE,
      'theme' => 'dark',
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 */
function media_avportal_variable_name($name) {
  return MEDIA_AVPORTAL_NAMESPACE . $name;
}
