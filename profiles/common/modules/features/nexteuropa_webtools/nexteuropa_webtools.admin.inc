<?php

/**
 * @file
 * Administration forms for the NextEuropa Webtools feature.
 */

/**
 * Form construction for the NextEuropa Webtools settings form.
 */
function nexteuropa_webtools_settings_form() {
  $form = array();

  $form['nexteuropa_webtools_smartloader_prurl'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarloader Protocol-Relative URL'),
    '#default_value' => variable_get('nexteuropa_webtools_smartloader_prurl', ''),
    '#description' => t("The URL of the webtools smartloader script. e.g. '//example.com/load.js'"),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
