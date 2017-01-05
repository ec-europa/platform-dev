<?php

/**
 * @file
 * Provides page callbacks and form functions for TMGMT Workbench.
 */

/**
 * Form callback for the settings form.
 *
 * @see system_settings_form()
 */
function tmgmt_workbench_settings_form(array $form, array &$form_state) {

  $options = array();
  foreach (workbench_moderation_states() as $key => $state) {
    $options[$key] = $state->label;
  }

  $form['workflow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Workbench Moderation states'),
    '#description' => t("Select which Workbench Moderation states are translatable."),
  );
  $form['workflow']['tmgmt_workbench_moderation_states'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available states'),
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => variable_get('tmgmt_workbench_moderation_states', array()),
  );

  $form['workflow']['tmgmt_workbench_moderation_always_show_direct_translation_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always show direct translation links'),
    '#description' => t('Choose if always show direct translation links, provided by Entity Translation module, regardless of the current moderation state.'),
    '#default_value' => variable_get('tmgmt_workbench_moderation_always_show_direct_translation_links', FALSE),
  );

  return system_settings_form($form);
}
