<?php
/**
 * @file
 * splash_screen.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function splash_screen_strongarm() {
  global $base_url;
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negotiation_language';
  $strongarm->value = array(
    'locale-url' => array(
      'callbacks' => array(
        'language' => 'locale_language_from_url',
        'switcher' => 'locale_language_switcher_url',
        'url_rewrite' => 'locale_language_url_rewrite_url',
      ),
      'file' => 'includes/locale.inc',
    ),
    'language_cookie' => array(
      'callbacks' => array(
        'language' => 'language_cookie_language',
        'switcher' => 'language_cookie_language_switcher',
        'url_rewrite' => 'language_cookie_language_rewrite',
      ),
      'file' => 'sites/all/modules/contributed/language_cookie/language_cookie.module',
      'cache' => 0,
    ),
    'language-default' => array(
      'callbacks' => array(
        'language' => 'language_from_default',
      ),
    ),
  );
  $export['language_negotiation_language'] = $strongarm;
  
  return $export;
}
