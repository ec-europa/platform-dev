<?php
/**
 * @file
 * Next Europa TMGMT DGT Rules configuration page callbacks.
 */

/**
 * Generates the cache purge rule editing form.
 */
function ne_tmgmt_dgt_rules_admin_settings_form($form, $form_state) {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration settings'),
  );
  $form['settings']['ftt_translations'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fast Track Translations'),
    '#description' => t('Configuration options for the fast track translation workflow.'),
  );

  $form['settings']['ftt_translations']['ne_tmgmt_dgt_rules_translator'] = array(
    '#title' => t('Default TMGMT translator'),
    '#type' => 'select',
    '#options' => tmgmt_translator_labels(),
    '#default_value' => variable_get('ne_tmgmt_dgt_rules_translator', array()),
    '#required' => TRUE,
    '#description' => t('Select the default TMGMT translator for the fast track translations workflow.'),
  );

  return system_settings_form($form);
}
