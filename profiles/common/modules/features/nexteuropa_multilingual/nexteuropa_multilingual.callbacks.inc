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
  $current_path = request_path();

  if (!language_negotiation_get_any('nexteuropa_multilingual_url_suffix')) {
    return $language_url;
  }

  // $_GET['q'] might not be available at this time, because
  // path initialization runs after the language bootstrap phase.
  $check_prefix = nexteuropa_multilingual_language_negotiation_split_suffix(isset($current_path) ? $current_path : NULL, $languages);
  if ($check_prefix[0] !== FALSE) {
    $language_url = $check_prefix[0]->language;
    $_GET['q'] = $check_prefix[1];
  }
  return $language_url;
}


/**
 * Function nexteuropa_multilingual_language_negotiation_url_rewrite_callback.
 *
 * @todo: Add documentation.
 */
function nexteuropa_multilingual_language_negotiation_url_rewrite_callback(&$path, &$options) {
  // Don't add the language suffix for an internal file URL.
  $file_public = variable_get('file_public_path', conf_path() . '/files');
  $file_private = 'system/files';
  if ($file_public && preg_match("#^/?$file_public#", $path) ||
    $file_private && preg_match("#^/?$file_private#", $path)) {
    return;
  }

  // Don't add the language suffix for sitemap.*** and ecas.
  if (strpos($path, 'sitemap.') === 0 || strpos($path, 'ecas') === 0) {
    return;
  }

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
  elseif (empty($options['language']->language) || !isset($languages[$options['language']->language])) {
    unset($options['language']);
    return;
  }

  // We don't add the language suffix if $path is empty.
  // We don't force the frontpage URL to $path if $path is empty.
  if (!empty($path)) {
    $path = drupal_get_path_alias(($path == '<front>') ? variable_get('site_frontpage', 'node') : $path, $options['language']->language);

    // Remove duplicate base_path in URL (NEXTEUROPA-9311).
    // Temporary fix until the next version of the link module.
    if (base_path() != '/' && strpos($path, base_path()) == 0) {
      $path = str_replace(base_path(), '', $path);
    }

    $language_suffix = _nexteuropa_multilingual_get_language_suffix($options['language']);

    // Check if the language suffix has been already added.
    $check_prefix = nexteuropa_multilingual_language_negotiation_split_suffix($path, $languages);
    $path = $check_prefix[1] . $delimiter . $language_suffix;

    $options['alias'] = TRUE;
  }

}


/**
 * Extract the suffix from the path.
 */
function nexteuropa_multilingual_language_negotiation_split_suffix($path, $languages) {
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
  $languages_prefix = array();
  // Use the suffix language.
  foreach ($languages as $language) {
    $languages_prefix[] = _nexteuropa_multilingual_get_language_suffix($language);
  }
  $pattern = '/' . $delimiter . '(' . implode($languages_prefix, '|') . ')(\/|$)/';
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
        $path .= ($path == '') ? '' : '/';
        $path .= implode("/", $extra_params);
      }
      // English does not have a prefix by default, so we add it for the future
      // comparisons that rely on prefix.
      $language->prefix = empty($language->prefix) ? $language->language : $language->prefix;

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
  if (is_object($language)) {
    if (!empty($language->prefix)) {
      return $language->prefix;
    }
    elseif (!empty($language->language)) {
      return $language->language;
    }
  }
  return NULL;
}

/**
 * Get source path given its alias. Return input path if no alias is found.
 *
 * @param string $path
 *    Relative Drupal path.
 *
 * @return string
 *    Source path if any, input path if none.
 */
function _nexteuropa_multilingual_get_source_path($path) {
  $result = db_select('url_alias', 'a')
    ->fields('a', ['source'])
    ->condition('a.alias', $path)
    ->execute()
    ->fetchAssoc();
  if (is_array($result) && !empty($result)) {
    return array_shift($result);
  }
  return $path;
}
