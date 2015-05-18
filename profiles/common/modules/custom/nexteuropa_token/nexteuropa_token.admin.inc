<?php

/**
 * @file
 * Administration pages callbacks.
 */

/**
 * Form callback for module settings.
 */
function nexteuropa_token_settings_form() {
  $form['hash_token'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hash token'),
  );
  $form['hash_token']['nexteuropa_token_hash_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Site prefix'),
    '#default_value' => variable_get('nexteuropa_token_hash_prefix', 'prefix'),
    '#description' => t("Site specific prefix used to seed hash token generation."),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}
