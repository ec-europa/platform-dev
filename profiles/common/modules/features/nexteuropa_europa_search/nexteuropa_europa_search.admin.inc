<?php

/**
 * @file
 * Idol admin search.
 */

/**
 * Form constructor for the Europa Search form.
 */
function nexteuropa_europa_search_admin_form(array $form, array $form_state) {
  $form['idol_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Europa Search settings'),
    '#collapsible' => TRUE,
  );
  $form['idol_settings']['nexteuropa_europa_search_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Europa Search URL'),
    '#default_value' => variable_get('nexteuropa_europa_search_url', NEXTEUROPA_EUROPA_SEARCH_EUROPA_SEARCH_URL),
    '#required' => TRUE,
  );
  $form['idol_settings']['nexteuropa_europa_search_language_negotiation'] = array(
    '#type' => 'select',
    '#title' => t('Default language'),
    '#options' => nexteuropa_europa_search_admin_available_languages(),
    '#default_value' => variable_get('nexteuropa_europa_search_language_negotiation', 'current'),
  );
  $form['idol_settings']['nexteuropa_europa_search_query_source'] = array(
    '#type' => 'textfield',
    '#title' => t('Subset name for Restricted Search'),
    '#default_value' => variable_get('nexteuropa_europa_search_query_source', NEXTEUROPA_EUROPA_SEARCH_EUROPA_SEARCH_QUERY_SOURCE),
    '#description' => t('See <a href="http://ec.europa.eu/ipg/services/search/search_en.htm">documentation</a> on how to create a subset on Europa Search.'),
  );
  $form = system_settings_form($form);
  return $form;
}

/**
 * Implements hook_form_validate().
 */
function nexteuropa_europa_search_admin_form_validate($form, &$form_state) {
  // Check if the url is a valid url.
  if (!filter_var($form_state['values']['nexteuropa_europa_search_url'], FILTER_VALIDATE_URL)) {
    form_set_error('nexteuropa_europa_search_url', t('The submitted value is not a valid url'));
  }
}

/**
 * Defines a list of the enabled languages on the site instance.
 *
 * @return array
 *   List of default languages + current page language
 */
function nexteuropa_europa_search_admin_available_languages() {
  $enabled_languages = language_list('enabled');
  $language_codes = array();
  $language_codes['current'] = t('Current language');
  foreach ($enabled_languages[1] as $enabled_language) {
    $language_codes[$enabled_language->language] = $enabled_language->name;
  }
  return $language_codes;
}
