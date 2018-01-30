<?php

/**
 * @file
 * Callbacks used to generate the administration section of the DGT Connector.
 */

/**
 * Generates the main DGT connector settings form.
 */
function tmgmt_dgt_connector_admin_settings_form($form, $form_state) {
  $form['dgt_connector'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#description' => t('General settings placeholder.'),
  );

  return system_settings_form($form);
}
