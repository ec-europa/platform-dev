<?php
/**
 * @file
 * multisite_settings_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function multisite_settings_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_cookie_domain';
  $strongarm->value = '';
  $export['language_cookie_domain'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_cookie_param';
  $strongarm->value = 'language';
  $export['language_cookie_param'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_cookie_path';
  $strongarm->value = '/';
  $export['language_cookie_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_cookie_time';
  $strongarm->value = '31536000';
  $export['language_cookie_time'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negotiation_language';
  $strongarm->value = array(
    'nexteuropa_multilingual_url_suffix' => array(
      'callbacks' => array(
        'language' => 'nexteuropa_multilingual_language_negotiation_provider_callback',
        'url_rewrite' => 'nexteuropa_multilingual_language_negotiation_url_rewrite_callback',
        'switcher' => 'nexteuropa_multilingual_language_negotiation_switcher_url',
      ),
      'file' => 'profiles/multisite_drupal_standard/modules/features/nexteuropa_multilingual/nexteuropa_multilingual.callbacks.inc',
    ),
    'language-default' => array(
      'callbacks' => array(
        'language' => 'language_from_default',
      ),
    ),
  );
  $export['language_negotiation_language'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negotiation_language_content';
  $strongarm->value = array(
    'locale-interface' => array(
      'callbacks' => array(
        'language' => 'locale_language_from_interface',
      ),
      'file' => 'includes/locale.inc',
    ),
  );
  $export['language_negotiation_language_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negotiation_language_url';
  $strongarm->value = array(
    'nexteuropa_multilingual_url_suffix' => array(
      'callbacks' => array(
        'language' => 'nexteuropa_multilingual_language_negotiation_provider_callback',
        'url_rewrite' => 'nexteuropa_multilingual_language_negotiation_url_rewrite_callback',
        'switcher' => 'nexteuropa_multilingual_language_negotiation_switcher_url',
      ),
      'file' => 'profiles/multisite_drupal_standard/modules/features/nexteuropa_multilingual/nexteuropa_multilingual.callbacks.inc',
    ),
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
      'file' => 'profiles/multisite_drupal_standard/modules/contrib/language_cookie/language_cookie.module',
    ),
    'locale-url-fallback' => array(
      'callbacks' => array(
        'language' => 'locale_language_url_fallback',
      ),
      'file' => 'includes/locale.inc',
    ),
  );
  $export['language_negotiation_language_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'locale_language_providers_weight_language';
  $strongarm->value = array(
    'locale-url' => '-8',
    'locale-session' => '-6',
    'language_cookie' => '-5',
    'locale-user' => '-4',
    'nexteuropa_multilingual_url_suffix' => -10,
    'locale-browser' => '-2',
    'language-default' => '10',
  );
  $export['locale_language_providers_weight_language'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'realname_pattern';
  $strongarm->value = '[user:field_firstname] [user:field_lastname]';
  $export['realname_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_default';
  $strongarm->value = 'ec_resp';
  $export['theme_default'] = $strongarm;

  return $export;
}
