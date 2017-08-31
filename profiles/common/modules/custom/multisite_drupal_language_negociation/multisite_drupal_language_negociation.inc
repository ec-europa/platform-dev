<?php
/**
 * @file
 * Language negotiation callbacks.
 */

define('MULTISITE_DRUPAL_LANGUAGE_NEGOCIATION_URL_SUFFIX', 'locale-url-suffix');

/**
 * Callback functions for the multisite language negotiation providers.
 */
function multisite_language_provider_callback($languages) {
  $language_url = FALSE;
  if (!language_negotiation_get_any(MULTISITE_DRUPAL_LANGUAGE_NEGOCIATION_URL_SUFFIX)) {
    return $language_url;
  }

  // $_GET['q'] might not be available at this time, because path initialization
  // runs after the language bootstrap phase.
  list($language, $_GET['q']) = language_url_split_suffix(isset($_GET['q']) ? $_GET['q'] : NULL, $languages);
  if ($language !== FALSE) {
    $language_url = $language->language;
  }

  return $language_url;
}

/**
 * Callback to rewrite URLs for the URL language provider.
 *
 * @see hook_language_negotiation_info()
 */
function multisite_url_rewrite_callback(&$path, &$options) {
  global $language_url;

  $delimiter = variable_get('language_suffix_delimiter', '_');

  $language_list = language_list('enabled');
  $languages = array_flip(array_keys($language_list[1]));

  // Language can be passed as an option, or we go for current URL language.
  if (!isset($options['language'])) {
    if (isset($options['attributes']['lang'])) {
      $options['language'] = $language_list[1][$options['attributes']['lang']];
    }
    else {
      $options['language'] = $language_url;
    }
  }
  // We allow only enabled languages here.
  elseif (!isset($languages[$options['language']->language])) {
    unset($options['language']);
    return;
  }

  $path = drupal_get_path_alias(empty($path) ? variable_get('site_frontpage', 'node') : $path, $options['language']->language);
  // Handle the homepage URL.
  if ($path == '<front>' || $path == '') {
    $path = variable_get('site_frontpage', 'node');
  }

  $path .= $delimiter . $options['language']->prefix;

  $options['alias'] = TRUE;
}

/**
 * Extract the suffix from the path.
 */
function language_url_split_suffix($path, $languages) {
  $delimiter = variable_get('language_suffix_delimiter', '_');
  $args = empty($path) ? array() : explode($delimiter, $path);
  $suffix = array_pop($args);
  // Handle if there are extra parameters after the suffix.
  $extra_params = explode("/", $suffix);
  $suffix = array_shift($extra_params);

  // Search prefix within enabled languages.
  foreach ($languages as $language) {
    if (!empty($language->prefix) && $language->prefix == $suffix) {
      // Rebuild $path with the language removed.
      $path = implode($delimiter, $args);
      // Handle the path homepage.
      $path = ($path == 'index') ? '' : $path;
      // Add extra params after suffix.
      if (count($extra_params) > 0) {
        $path .= "/" . implode("/", $extra_params);
      }
      return array($language, $path);
    }
  }
  return array(FALSE, $path);
}

/**
 * Language switcher callback.
 *
 * @see hook_language_negotiation_info()
 */
function multisite_language_switcher_url($type, $path) {
  $languages = language_list('enabled');
  $links = array();
  foreach ($languages[1] as $language) {
    $links[$language->language] = array(
      'href' => $path,
      'title' => $language->native,
      'language' => $language,
      'attributes' => array('class' => array('language-link')),
    );
  }
  return $links;
}
