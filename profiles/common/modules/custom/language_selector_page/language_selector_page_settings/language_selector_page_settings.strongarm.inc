<?php
/**
 * @file
 * language_selector_page_settings.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function language_selector_page_settings_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_default';
  $strongarm->value = (object) array(
    'language' => 'en',
    'name' => 'English',
    'native' => 'English',
    'direction' => '0',
    'enabled' => 1,
    'plurals' => '0',
    'formula' => '',
    'domain' => '',
    'prefix' => 'en',
    'weight' => -14,
    'javascript' => '',
  );
  $export['language_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'locale_language_negotiation_session_param';
  $strongarm->value = '2nd-language';
  $export['locale_language_negotiation_session_param'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'locale_language_providers_weight_language_content';
  $strongarm->value = array(
    'locale-session' => '-10',
    'nexteuropa_multilingual_url_suffix' => '-8',
    'language-default' => '-9',
    'locale-interface' => '-7',
    'locale-url' => '-6',
    'language_cookie' => '-5',
    'locale-user' => '-4',
    'locale-browser' => '-3',
  );
  $export['locale_language_providers_weight_language_content'] = $strongarm;

  return $export;
}
