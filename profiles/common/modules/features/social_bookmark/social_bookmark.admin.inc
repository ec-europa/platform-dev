<?php

/**
 * @file
 * Admin page callbacks for the social bookmark module.
 */

/**
 * Implements configuration form().
 */
function _social_bookmark_admin_settings() {
  $form = array();

  $form['style_socialbookmark'] = array(
    '#type' => 'fieldset',
    '#title' => t('Customize widget look'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['style_socialbookmark']['type_socialbookmark'] = array(
    '#type' => 'radios',
    '#title' => t('Widget type'),
    '#default_value' => variable_get('type_socialbookmark', 'Button'),
    '#options' => drupal_map_assoc(array(
      0 => t('Button'),
      1 => t('Icon'),
    )),
    '#description' => t('Choose the widget you prefer.'),
  );

  $form['style_socialbookmark']['icon_size_socialbookmark'] = array(
    '#type' => 'select',
    '#title' => t('Icon size (px)'),
    '#options' => drupal_map_assoc(array(
      0 => t('16'),
      1 => t('18'),
      2 => t('20'),
      3 => t('24'),
      4 => t('32'),
    )),
    '#default_value' => variable_get('icon_size_socialbookmark', '16'),
    '#description' => t('Size of the icon in pixels (only available for the "Icon" widget type).'),
  );

  $form['style_socialbookmark']['override_socialbookmark'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override default label'),
    '#default_value' => variable_get('override_socialbookmark', FALSE),
    '#description' => t('Set the text to display on the button / icon. </br>If it is not selected, it uses the default label "Share" in the appropriate language.'),
  );

  $form['style_socialbookmark']['label_socialbookmark'] = array(
    '#type' => 'textfield',
    '#title' => t('New label'),
    '#size' => 30,
    '#maxlength' => 128,
    '#default_value' => variable_get('label_socialbookmark'),
  );

  $form['counter_socialbookmark'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display counter'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['counter_socialbookmark']['display_socialbookmark'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display/hide counter'),
    '#default_value' => variable_get('display_socialbookmark', FALSE),
    '#description' => t('By default counter display is disabled. In order to unable it, check this parameter.'),
  );

  $form['counter_socialbookmark']['least_socialbookmark'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum "shares" for display'),
    '#size' => 5,
    '#maxlength' => 128,
    '#default_value' => variable_get('least_socialbookmark', ''),
    '#description' => t('Counter will be displayed if at least X sharings have been made. </br>Leave it blank to always display counter.'),
  );

  $form['counter_socialbookmark']['orientation_socialbookmark'] = array(
    '#type' => 'radios',
    '#title' => t('Counter position'),
    '#default_value' => variable_get('orientation_socialbookmark', 'Right'),
    '#options' => drupal_map_assoc(array(
      0 => t('Right'),
      1 => t('Left'),
    )),
    '#description' => t('Choose where the counter should be displayed.'),
  );

  $form['statistics'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enable/disable statistics'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['statistics']['statistics_socialbookmark'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable/disable statistics'),
    '#default_value' => variable_get('statistics_socialbookmark', TRUE),
    '#description' => t('By default statistics are enabled. In order to disable it, uncheck this parameter.'),
  );

  $form['language_detection'] = array(
    '#type' => 'fieldset',
    '#title' => t("Modify language's detection"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['language_detection']['language_socialbookmark'] = array(
    '#type' => 'radios',
    '#title' => t('Language source'),
    '#default_value' => variable_get('language_socialbookmark', 'From META DATA'),
    '#options' => drupal_map_assoc(array(
      0 => t('From URL'),
      1 => t('From META DATA'),
      2 => t('Language specified'),
    )),
    '#description' => t('In order to change the language detection you should use this options. </br>If this parameter is not defined, the application tries to detect the language automatically from META DATA.'),
  );
  global $language;
  $languages = language_list('enabled');
  $langs = array();
  foreach ($languages[1] as $lan) {
    $langs[$lan->language] = $lan->name;
  }

  $form['language_detection']['language_selector_socialbookmark'] = array(
    '#type' => 'select',
    '#title' => t('Set a specific language'),
    '#options' => $langs,
    '#default_value' => variable_get('language_selector_socialbookmark', $language->language),
    '#description' => t('Select a language (only available for the "Language specified" option)."'),
  );

  $form['custom_user'] = array(
    '#type' => 'fieldset',
    '#title' => t('Customize “via @username” mention for Twitter'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['custom_user']['user_value_socialbookmark'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter username'),
    '#size' => 30,
    '#maxlength' => 128,
    '#default_value' => variable_get('user_value_socialbookmark', 'EU_Commission'),
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'social_bookmark') . '/scripts/social_bookmark.form.js',
  );
  return system_settings_form($form);
}
