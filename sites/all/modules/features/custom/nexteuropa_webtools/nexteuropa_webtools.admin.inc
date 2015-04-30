<?php
function nexteuropa_webtools_settings_form() {
  $form = array();

  $form['nexteuropa_webtools_smarloader_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarloader URL'),
    '#default_value' => variable_get('nexteuropa_webtools_smarloader_url', ''),
    '#description' => t("The URL of the webtools smartloader script (load.js)"),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

