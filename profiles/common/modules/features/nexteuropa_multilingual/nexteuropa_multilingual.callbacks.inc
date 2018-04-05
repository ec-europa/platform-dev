<?php

/**
 * @file
 * Nexteuropa_multilingual.callbacks.inc.
 */

/**
 * Callback functions for the nexteuropa language negotiation providers.
 */
function nexteuropa_multilingual_language_negotiation_provider_callback($languages) {
  $current_path = request_path();

  // $_GET['q'] might not be available at this time, because
  // path initialization runs after the language bootstrap phase.
  if (empty($current_path)) {
    return FALSE;
  }

  // If not enabled, the process is stop and Drupal passes to the next language
  // negotiation mechanism.
  if (!language_negotiation_get_any('nexteuropa_multilingual_url_suffix')) {
    return FALSE;
  }

  $check_prefix = nexteuropa_multilingual_language_negotiation_split_suffix($current_path, $languages);
  if ($check_prefix[0] === FALSE) {
    return FALSE;
  }

  $_GET['q'] = $check_prefix[1];

  return $check_prefix[0]->language;
}


/**
 * Function nexteuropa_multilingual_language_negotiation_url_rewrite_callback.
 *
 * We add the suffix using the delimiter that is chosen in config screens.
 */
function nexteuropa_multilingual_language_negotiation_url_rewrite_callback(&$path, &$options) {
  if (empty($path)) {
    return;
  }

  // Some paths should not have a suffix.
  $exceptions = array();
  $exceptions[] = variable_get('file_public_path', conf_path() . '/files');
  $exceptions[] = 'system/files';
  $exceptions[] = 'sitemap';
  $exceptions[] = 'ecas';
  $exceptions[] = '<front>';

  foreach ($exceptions as $exception) {
    if (preg_match("#^/?$exception#", $path)) {
      return;
    }
  }

  // Load languages in the static cache.
  // Taken from locale_language_url_rewrite_url().
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['languages_suffix'] = &drupal_static(__FUNCTION__);
  }
  $languages = &$drupal_static_fast['languages_suffix'];

  if (!isset($languages)) {
    $languages = language_list('enabled');
    $languages = $languages[1];
  }

  // Language can be passed as an option, or we go for current URL language.
  if (!isset($options['language'])) {
    if (isset($options['attributes']['lang'])) {
      $options['language'] = $languages[$options['attributes']['lang']];
    }
    else {
      global $language_url;
      $options['language'] = $language_url;
    }
  }
  // We allow only enabled languages here.
  elseif (empty($options['language']->language) || !isset($languages[$options['language']->language])) {
    unset($options['language']);
    return;
  }

  // Treat the path to append the suffix.
  $path = drupal_get_path_alias($path, $options['language']->language);

  // Remove duplicate base_path in URL (NEXTEUROPA-9311).
  // Temporary fix until the next version of the link module.
  if (base_path() != '/' && strpos($path, base_path()) === 0) {
    $path = str_replace(base_path(), '', $path);
  }

  $language_suffix = _nexteuropa_multilingual_get_language_suffix($options['language']);

  // Check if the language suffix has been already added.
  $delimiter = variable_get('nexteuropa_multilingual_language_suffix_delimiter', '_');
  $check_prefix = nexteuropa_multilingual_language_negotiation_split_suffix($path, $languages);
  $path = $check_prefix[1] . $delimiter . $language_suffix;

  $options['alias'] = TRUE;
}

/**
 * Extract the suffix from the path.
 *
 * @param string $path
 *   The path where to extract the suffix.
 * @param array $languages
 *   An array of valid language objects.
 *
 * @return array
 *   The path split in 2 elements:
 *   - The language object deduced from the suffix, or FALSE if not found;
 *   - The patch without the suffix.
 */
function nexteuropa_multilingual_language_negotiation_split_suffix($path, array $languages) {
  $delimiter = variable_get('nexteuropa_multilingual_language_suffix_delimiter', '_');

  if (_nexteuropa_multilingual_get_source_path($path) != $path) {
    return array(FALSE, $path);
  }

  // Handle adding an Entity Translation field to a view with Estonian enabled.
  // @link https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-107
  if (preg_match("/^admin\/structure\/views\/.+\/field\/\w+\_et$/", $path, $matches)) {
    // Still related to the ticket NEPT-107.
    // If the Views interface is accessed in Estonian ("_et_et" suffix exist),
    // then the function process must go on, otherwise we stop here and
    // it returns FALSE for the path.
    if (strrpos($path, '_et_et', -6) === FALSE) {
      return array(FALSE, $path);
    }
  }

  // Forcing to use the prefix at the end of the path with the delimiter '_'.
  // example:
  // /foo/bar_en  (supported),
  // /_en/foo/bar (not supported),
  // /en/foo/bar  (not supported).
  $languages_with_suffix = _nexteuropa_multilingual_get_languages_with_suffix($languages);

  $languages_suffix = array_keys($languages_with_suffix);
  $pattern = '/' . $delimiter . '(' . implode($languages_suffix, '|') . ')(\/|$)/';
  // Search the language suffix with the delimiter in the path.
  if (!preg_match($pattern, $path)) {
    // No language suffix found.
    return array(FALSE, $path);
  }

  $args = empty($path) ? array() : explode($delimiter, $path);
  $suffix = array_pop($args);

  // Handle if there are extra parameters after the suffix.
  $extra_params = explode("/", $suffix);
  $suffix = array_shift($extra_params);

  if (!isset($languages_with_suffix[$suffix])) {
    return array(FALSE, $path);
  }

  // Search prefix within enabled languages.
  $language = $languages_with_suffix[$suffix];

  // Rebuild $path with the language removed.
  $path = implode($delimiter, $args);
  // Handle the path homepage.
  $path = ($path == 'index') ? '' : $path;
  // Add extra params after suffix.
  if (count($extra_params) > 0) {
    $path .= ($path == '') ? '' : '/';
    $path .= implode("/", $extra_params);
  }

  return array($language, $path);
}

/**
 * Return the URL for language switcher block.
 *
 * The translation links may be provided by other modules.
 *
 * @param string $type
 *   The URL type.
 * @param string $path
 *   The patch on which generate the urls.
 *
 * @return array
 *   An array of
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
 * Gets the list of suffixes corresponding to languages set in the site.
 *
 * @param array $languages
 *   An array of valid language objects.
 *
 * @return array
 *   An array of the language objects keyed by their corresponding suffix.
 */
function _nexteuropa_multilingual_get_languages_with_suffix(array $languages = array()) {
  $suffix_list = array();

  // Use the suffix language.
  foreach ($languages as $language) {
    $language_suffix = _nexteuropa_multilingual_get_language_suffix($language);

    if (!empty($language_suffix)) {
      $suffix_list[$language_suffix] = $language;
    }
  }

  return $suffix_list;
}

/**
 * Gets the language suffix for the language passed as parameter.
 *
 * The suffix corresponds to language prefix stored in DB. If not defined, the
 * langcode is used.
 * This suffix is used on the last part of the URL.
 *
 * @param stdClass $language
 *   The language object from which extract the suffix.
 *
 * @return string
 *   The suffix value.
 */
function _nexteuropa_multilingual_get_language_suffix($language) {
  if (is_object($language)) {
    if (!empty($language->prefix)) {
      return $language->prefix;
    }

    if (!empty($language->language)) {
      return $language->language;
    }
  }

  return FALSE;
}

/**
 * Get source path given its alias. Return input path if no alias is found.
 *
 * @param string $path
 *   Relative Drupal path.
 *
 * @return string
 *   Source path if any, input path if none.
 */
function _nexteuropa_multilingual_get_source_path($path) {
  $result = drupal_lookup_path('source', $path);

  if (!empty($result)) {
    return $result;
  }

  return $path;
}
