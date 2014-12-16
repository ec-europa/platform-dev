<?php

/**
 * @file media_avportal/includes/media_avportal.variables.inc
 *
 * Variable defaults for Media: Avportal.
 */

/**
 * Define our constants.
 */

/**
 * This is the variable namespace, automatically prepended to module variables.
 */
define('MEDIA_AVPORTAL_NAMESPACE', 'media_avportal__');

/**
 * This is the rest point for the Avportal api.
 *
 * Avoid using the gdata api url when possible. Too many calls will result in
 * throttling and 403 errors.
 */
define('MEDIA_AVPORTAL_REST_API', 'https://gdata.avportal.com/feeds/api/videos');

/**
 * Variable system uses Ctools Exportables.
 */

/**
 * Wrapper for variable_get() using the Media: Avportal variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending MEDIA_AVPORTAL_NAMESPACE, as to avoid variable collisions
 *  with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the media_avportal_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see media_avportal_variable_set()
 * @see media_avportal_variable_del()
 * @see media_avportal_variable_default()
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
 * Wrapper for variable_set() using the Media: Avportal variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending MEDIA_AVPORTAL_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see media_avportal_variable_get()
 * @see media_avportal_variable_del()
 * @see media_avportal_variable_default()
 */
function media_avportal_variable_set($name, $value) {
  $variable_name = MEDIA_AVPORTAL_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the Media: Avportal variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending MEDIA_AVPORTAL_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 *
 * @see media_avportal_variable_get()
 * @see media_avportal_variable_set()
 * @see media_avportal_variable_default()
 */
function media_avportal_variable_del($name) {
  $variable_name = MEDIA_AVPORTAL_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Media: Avportal namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been prepended with the MEDIA_AVPORTAL_NAMESPACE namespace at this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see media_avportal_variable_get()
 * @see media_avportal_variable_set()
 * @see media_avportal_variable_del()
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
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  MEDIA_AVPORTAL_NAMESPACE.
 */
function media_avportal_variable_name($name) {
  return MEDIA_AVPORTAL_NAMESPACE . $name;
}
