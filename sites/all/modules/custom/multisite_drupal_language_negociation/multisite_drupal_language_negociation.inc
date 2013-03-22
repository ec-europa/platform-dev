<?php
define('LOCALE_LANGUAGE_NEGOTIATION_URL_SUFFIX', 'locale-url-suffix');
/**
  * callback functions for the multisite language negotiation providers, module : multisite_drupal_language_negociation
  */
function multisite_language_provider_callback($languages) {
  $language_url = FALSE;
  if (!language_negotiation_get_any(LOCALE_LANGUAGE_NEGOTIATION_URL_SUFFIX)) {
    return $language_url;
  }

  // $_GET['q'] might not be available at this time, because
  // path initialization runs after the language bootstrap phase.
  list($language, $_GET['q']) = language_url_split_suffix(isset($_GET['q']) ? $_GET['q'] : NULL, $languages);
  if ($language !== FALSE) {
    $language_url = $language->language;
  }

  return $language_url;
}

/*
 * extract the suffix from the path 
 */
function language_url_split_suffix($path, $languages) {
  $delimiter = variable_get('language_suffix_delimiter','_');
  $args = empty($path) ? array() : explode($delimiter, $path);
  $suffix = array_pop($args);

  // Search prefix within enabled languages.
  foreach ($languages as $language) {
    if (!empty($language->prefix) && $language->prefix == $suffix) {
      // Rebuild $path with the language removed.
      return array($language, implode($delimiter, $args));
    }
  }
  return array(FALSE, $path);
}


/**
  * Rewrite URLs for the URL language provider.
  */
/*
function multisite_url_rewrite_callback(&$path, &$options) {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['languages'] = &drupal_static(__FUNCTION__);
  }
  $languages = &$drupal_static_fast['languages'];

  if (!isset($languages)) {
    $languages = language_list('enabled');
    $languages = array_flip(array_keys($languages[1]));
  }

  // Language can be passed as an option, or we go for current URL language.
  if (!isset($options['language'])) {
    global $language_url;
    $options['language'] = $language_url;
  }
  // We allow only enabled languages here.
  elseif (!isset($languages[$options['language']->language])) {
    unset($options['language']);
    return;
  }
 
  if (isset($options['language'])) {
    if (!empty($options['language']->prefix)) {
      //$options['prefix'] = $options['language']->prefix . '/';
      $suffix = variable_get('language_suffix_delimiter','_');
      if ($path == '<front>') {
        $fp = variable_get('site_frontpage', 'node');
        $path = $fp.$suffix.$options['language']->prefix;
      }
      else
        $path .= $suffix.$options['language']->prefix;
      
    }
  }
}
*/
