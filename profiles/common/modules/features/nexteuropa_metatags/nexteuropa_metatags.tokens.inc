<?php

/**
 * @file
 * Tokens for the NextEuropa Metatags feature.
 */

/**
 * Implements hook_token_info().
 */
function nexteuropa_metatags_token_info() {
  // Language tokens.
  $info['types']['language'] = array(
    'name' => t('Language'),
    'description' => t('Tokens related to site language.'),
  );
  $info['tokens']['language']['language-ui'] = array(
    'name' => t('User Interface'),
    'description' => t('Tokens related to the active user interface language.'),
    'type' => 'language-ui',
  );
  $info['tokens']['language']['language-content'] = array(
    'name' => t('Content'),
    'description' => t('Tokens related to the active content language.'),
    'type' => 'language-content',
  );
  // User interface language tokens.
  $info['types']['language-ui'] = array(
    'name' => t('Language UI'),
    'description' => t('Tokens related to the active user interface language.'),
    'needs-data' => 'language-ui',
  );
  $info['tokens']['language-ui']['language'] = array(
    'name' => t('Code'),
    'description' => t('The active user interface language code.'),
  );
  $info['tokens']['language-ui']['name'] = array(
    'name' => t('Name'),
    'description' => t('The active user interface language name.'),
  );
  $info['tokens']['language-ui']['native'] = array(
    'name' => t('Native name'),
    'description' => t('The active user interface native language name.'),
  );

  // Content language tokens.
  $info['types']['language-content'] = array(
    'name' => t('Language Content'),
    'description' => t('Tokens related to the active content language.'),
    'needs-data' => 'language-content',
  );
  $info['tokens']['language-content']['language'] = array(
    'name' => t('Code'),
    'description' => t('The active content language code.'),
  );
  $info['tokens']['language-content']['name'] = array(
    'name' => t('Name'),
    'description' => t('The active content language name.'),
  );
  $info['tokens']['language-content']['native'] = array(
    'name' => t('Native name'),
    'description' => t('The active content language native name.'),
  );
  // File fid token.
  $info['types']['files'] = array(
    'name' => t('Files'),
    'description' => t('Reference a file entity by using its fid'),
  );
  $info['tokens']['files']['uri'] = array(
    'name' => t('Files uri'),
    'description' => t('Reference a file entity by using its fid'),
    'dynamic' => TRUE,
  );
  $info['tokens']['files']['uri']['fid'] = array(
    'name' => t('Files fid'),
    'description' => t('Reference a file entity by using its fid'),
    'dynamic' => TRUE,
  );
  return $info;
}


/**
 * Implements hook_tokens().
 */
function nexteuropa_metatags_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  // Language tokens.
  $replacements = array();
  if ($type == 'language') {
    global $language, $language_content;
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'language-content':
          $replacements[$original] = token_render_array((array) $language_content);
          break;

        case 'language-ui':
          $replacements[$original] = token_render_array((array) $language);
          break;
      }
    }
    // Content language tokens.
    if ($language_content_tokens = token_find_with_prefix($tokens, 'language-content')) {
      foreach ($language_content_tokens as $name => $original) {
        switch ($name) {
          case 'language':
            $replacements[$original] = $sanitize ? check_plain($language_content->language) : $language_content->language;
            break;

          case 'name':
            $replacements[$original] = $sanitize ? check_plain($language_content->name) : $language_content->name;
            break;

          case 'native':
            $replacements[$original] = $sanitize ? check_plain($language_content->native) : $language_content->native;
            break;
        }
      }
    }

    // UI language tokens.
    if ($language_ui_tokens = token_find_with_prefix($tokens, 'language-ui')) {
      foreach ($language_ui_tokens as $name => $original) {
        switch ($name) {
          case 'language':
            // Replace with prefix unless empty.
            $replacements[$original] = empty($language->prefix) ? $language->language : $language->prefix;
            break;

          case 'name':
            $replacements[$original] = $language->name;
            break;

          case 'native':
            $replacements[$original] = $language->native;
            break;
        }
      }
    }
  }

  if ($type == 'files') {
    if ($query_tokens = token_find_with_prefix($tokens, 'uri')) {
      foreach ($query_tokens as $name => $original) {
        if (is_numeric($name)) {
          $file = file_load($name);
          $replacements[$original] = token_render_array((array) $file->uri);
        }
      }
    }
  }
  return $replacements;
}
