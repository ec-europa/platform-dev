<?php

/**
 * @file
 * This file provides administration form for the module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function nexteuropa_cookie_consent_kit_form_cce_basic_config_settings_form_alter(&$form, &$form_state) {
  $form['webtools']['banner'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cookie consent kit configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 9,
    '#access' => user_access('administer nexteuropa cookie consent kit configuration'),
  );
  $form['webtools']['banner']['nexteuropa_cookie_consent_kit_display_cookie_banner'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the cookie banner'),
    '#default_value' => variable_get('nexteuropa_cookie_consent_kit_display_cookie_banner', 0),
    '#description' => theme('item_list', array(
      'items' => array(
        t('Tick this option to activate cookie consent kit on all pages.'),
        t('For more information about Webtools Cookie Consent Kit, click <a href="@url">here</a>.', array(
          '@url' => url('https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+V2', array('external' => TRUE)),
        )),
      ),
    )),
  );
  $form['webtools']['banner']['settings'] = array(
    '#type' => 'fieldset',
    '#states' => array(
      'visible' => array(
        ':input[name="nexteuropa_cookie_consent_kit_display_cookie_banner"]' => array(
          'checked' => TRUE,
        ),
      ),
    ),
  );
  $form['webtools']['banner']['settings']['nexteuropa_cookie_consent_kit_policy_url'] = array(
    '#type' => 'textarea',
    '#title' => t('Policy url'),
    '#default_value' => variable_get('nexteuropa_cookie_consent_kit_policy_url', ''),
    '#description' => theme('item_list', array(
      'items' => array(
        t('For non ec.europa.eu domains, you should specify the url to the cookie policy page as either a single string of text or multiple strings in json format.'),
        t('See some examples: !examples', array(
          '!examples' => theme('item_list', array(
            'items' => array(
              'https://example.com/cookie-policy',
              'https://example.com/cookie-policy_{lang} <strong>TIP:</strong> A placeholder {lang} is available and will be replaced with the language code of the page being displayed.',
              '{"en": "https://example.com/cookie-policy_en","de": "https://example.com/de/cookie-policy"}',
            ),
          )),
        )),
        t('For more information about Webtools Cookie Consent Kit, click <a href="@url">here</a>.', array(
          '@url' => url('https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+V2', array('external' => TRUE)),
        )),
      ),
    )),
  );
  $form['webtools']['banner']['settings']['nexteuropa_cookie_consent_kit_appendix'] = array(
    '#type' => 'textarea',
    '#title' => t('Appendix'),
    '#default_value' => variable_get('nexteuropa_cookie_consent_kit_appendix', ''),
    '#description' => theme('item_list', array(
      'items' => array(
        t('For non ec.europa.eu domains, the appendix is appended a to the cookie consent disclaimer. It can be provided as a single string of text or multiple strings for each language in json format.'),
        t('See some examples: !examples', array(
          '!examples' => theme('item_list', array(
            'items' => array(
              'Extra content in English only',
              '{"en": "Extra content in English","de": "Extra content in German"}',
            ),
          )),
        )),
        t('For more information about Webtools Cookie Consent Kit, click <a href="@url">here</a>.', array(
          '@url' => url('https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+V2', array('external' => TRUE)),
        )),
      ),
    )),
  );

  $form['webtools']['banner']['settings']['video'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video settings'),
  );
  $form['webtools']['banner']['settings']['video']['nexteuropa_cookie_consent_kit_display_cookie_video'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a specific cookie consent banner with all 3rd party video platform players (YouTube, Vimeo and Dailymotion)'),
    '#default_value' => variable_get('nexteuropa_cookie_consent_kit_display_cookie_video', 0),
    '#description' => theme('item_list', array(
      'items' => array(
        t('To be activated in case the only consent-required cookies in your site are created by embedded videos, otherwise the Cookie Banner is enough.'),
        t('For more information about Webtool Cookie Consent Kit for videos and other iframe content, click <a href="@url">here</a>.', array(
          '@url' => url('https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+for+videos+and+other+iframe+content', array('external' => TRUE)),
        )),
      ),
    )),
  );

  return $form;
}
