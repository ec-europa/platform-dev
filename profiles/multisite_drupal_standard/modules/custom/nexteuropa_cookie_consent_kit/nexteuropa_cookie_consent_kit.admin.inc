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
function nexteuropa_cookie_consent_kit_admin_form(array $form, array $form_state) {
  $form = array();
  $form['banner'] = array(
    '#type' => 'fieldset',
    '#title' => t('Banner settings'),
  );
  $form['banner']['nexteuropa_cookie_consent_kit_display_cookie_banner'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the cookie banner'),
    '#default_value' => variable_get('nexteuropa_cookie_consent_kit_display_cookie_banner', 0),
    '#description' => t("After activating this option, you need to make sure that the @consent file is being the first loaded JS file in the head tag in all your website's pages.", array(
      '@consent' => 'consent.js'
    )),
  );

  return system_settings_form($form);
}
