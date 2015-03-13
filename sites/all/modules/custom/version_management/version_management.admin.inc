<?php
/**
 * @file
 * Admin callbacks for the version_management module.
 */

/**
 * Build the admin settings form.
 */
function version_management_settings() {

  $form = array();
  $form['version_management_node_types_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Allow major versions'),
    '#description' => t('Enables the major version edit checkbox on allowed content types.'),
    '#prefix' => '<div class="version_management-toggles">',
    '#suffix' => '</div>',
  );
  $form['version_management_node_types_fieldset']['version_management_node_types'] = array(
    '#type' => 'checkboxes',
    '#options' => node_type_get_names(),
    '#default_value' => variable_get('version_management_node_types', array('')),
  );
  return system_settings_form($form);
}
