<?php

/**
 * @file
 * This file provides administration form for the module.
 */

/**
 * Provides form for cookie control banner.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   For state array.
 *
 * @return array
 *   Admin form render array.
 */
function nexteuropa_cookie_consent_kit_admin_form(array $form, array &$form_state) {
  $form['banner'] = array(
    '#type' => 'fieldset',
    '#title' => t('Banner settings'),
  );
  $form['banner']['nexteuropa_cookie_consent_kit_display_cookie_banner'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the cookie banner'),
    '#default_value' => variable_get('nexteuropa_cookie_consent_kit_display_cookie_banner', 0),
    '#description' => theme('item_list', array(
      'items' => array(
        t("After activating this option, you need to make sure that the @consent file is the first loaded JS file in the head tag in all your website's pages.", array(
          '@consent' => 'consent.js',
        )),
        t("If it is required, when a site creates a persistent cookie, this cookie should be listed in your site's @cookie_config.", array(
          '@cookie_config' => 'cookie_config.js',
        )),
        t('For more information about Webtool Cookie Consent Kit, click <a href="@url">here</a>.', array(
          '@url' => url('https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Cookie+Consent+Kit+-+Technical+details', array('external' => TRUE)),
        )),
      ),
    )),
  );

  $form['video'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video settings'),
  );
  $form['video']['nexteuropa_cookie_consent_kit_display_cookie_video'] = array(
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

  return system_settings_form($form);
}
