<?php

/**
 * @file
 * Default theme settings.
 */

/**
 * Add toogle option to theme settings to enable/disable dropdown menu.
 */
function ec_resp_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['dropdown_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dropdown menu settings'),
  );

  $form['dropdown_fieldset']['disable_dropdown_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable dropdown menu'),
    '#default_value' => theme_get_setting('disable_dropdown_menu'),
  );
}
