<?php
/**
 * @file
 * Nexteuropa_multilingual.callbacks.inc.
 */

/**
 * Callback functions for the nexteuropa language negotiation providers.
 */
function nexteuropa_multilingual_language_negotiation_provider_callback($languages) {
  $language_url = FALSE;
  if (!language_negotiation_get_any('nexteuropa_multilingual_url_suffix')) {
    return $language_url;
  }

  // $_GET['q'] might not be available at this time, because
  // path initialization runs after the language bootstrap phase.
  list($language, $_GET['q']) = nexteuropa_multilingual_language_negotiation_split_suffix(isset($_GET['q']) ? $_GET['q'] : NULL, $languages);
  if ($language !== FALSE) {
    $language_url = $language->language;
  }
  return $language_url;
}


/**
 * Function nexteuropa_multilingual_language_negotiation_url_rewrite_callback.
 *
 * @todo: Add documentation.
 */
function nexteuropa_multilingual_language_negotiation_url_rewrite_callback(&$path, &$options) {
  $delimiter = variable_get('nexteuropa_multilingual_language_suffix_delimiter', '_');
  $language_list = language_list('enabled');
  $languages = $language_list[1];

  // Language can be passed as an option, or we go for current URL language.
  if (!isset($options['language'])) {
    if (isset($options['attributes']['lang'])) {
      $options['language'] = $language_list[1][$options['attributes']['lang']];
    }
    else {
      global $language_url;
      $options['language'] = $language_url;
    }
  }
  // We allow only enabled languages here.
  elseif (!isset($languages[$options['language']->language])) {
    unset($options['language']);
    return;
  }

  $path = drupal_get_path_alias(empty($path) ? variable_get('site_frontpage', 'node') : $path, $options['language']->language);

  // Handle the homepage url.
  if ($path == '<front>' || $path == '') {
    $path = drupal_get_path_alias(variable_get('site_frontpage', 'node'));
  }

  $language_suffix = _nexteuropa_multilingual_get_language_suffix($options['language']);
  $path .= $delimiter . $language_suffix;

  $options['alias'] = TRUE;
}


/**
 * Extract the suffix from the path.
 */
function nexteuropa_multilingual_language_negotiation_split_suffix($path, $languages) {
  $delimiter = variable_get('nexteuropa_multilingual_language_suffix_delimiter', '_');
  $args = empty($path) ? array() : explode($delimiter, $path);
  $suffix = array_pop($args);
  // Handle if there are extra parameters after the suffix.
  $extra_params = explode("/", $suffix);
  $suffix = array_shift($extra_params);
  // Search prefix within enabled languages.
  foreach ($languages as $language) {
    $language_suffix = _nexteuropa_multilingual_get_language_suffix($language);
    if ($language_suffix && $language_suffix == $suffix) {
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
 * Function nexteuropa_multilingual_language_negotiation_switcher_url.
 *
 * @todo: Add documentation.
 */
function nexteuropa_multilingual_language_negotiation_switcher_url($type, $path) {
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

/**
 * Return the language suffix for the language passed as parameter.
 *
 * Suffix corresponds to language prefix. If not defined, the langcode is used.
 * This suffix is used on the last part of the URL.
 */
function _nexteuropa_multilingual_get_language_suffix($language) {
  if (is_object($language) && isset($language->language)) {
    if (isset($language->prefix) && !empty($language->prefix)) {
      return $language->prefix;
    }
    elseif (!empty($language->language)) {
      return $language->language;
    }
  }
  return NULL;
}
