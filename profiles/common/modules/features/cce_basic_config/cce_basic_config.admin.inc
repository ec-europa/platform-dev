<?php
/**
 * @file
 * Administration forms for the NextEuropa Webtools features.
 */

/**
 * Form construction for the NextEuropa Webtools settings form.
 */
function cce_basic_config_settings_form() {
  $form = array();
  $form['global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration for webtools widgets.'),
    '#description' => t('By default only the global banner is enabled. <br> In order to enable the Piwik widget, you need to send a request to CEM.'),
  );
  $form['global']['nexteuropa_webtools_smartloader_prurl'] = array(
    '#type' => 'textfield',
    '#title' => t('Smartloader Protocol-Relative URL'),
    '#default_value' => variable_get('nexteuropa_webtools_smartloader_prurl', ''),
    '#description' => t("The URL of the webtools smartloader script. e.g. '//example.com/load.js'"),
    '#required' => TRUE,
  );
  
  $form['global']['globan']= array(
    '#type' => 'fieldset',
    '#title' => t('GLOBAN configuration'),
    '#description' => t('Please check the <a href="@doclink">documentation wiki</a>.', array(
  '@doclink' => 'https://webgate.ec.europa.eu/fpfis/wikis/display/webtools/Global+banner')),
    '#weight' => 10,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  // Add a variable that allows users to hide the global banner.
  $form['global']['globan']['webtoolds_globan'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the global banner'),
    '#description' => t("Uncheck this box if you do not want the banner to show."),
    '#default_value' => variable_get('webtoolds_globan', 1),
  );
  $form['global']['globan']['cce_basic_config_globan_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => array(
      'dark' => 'dark',
      'light' => 'light',
    ),
    '#default_value' => variable_get('cce_basic_config_globan_theme', 'dark'),
  );
  $form['global']['globan']['cce_basic_config_globan_logo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Logo'),
    '#default_value' => variable_get('cce_basic_config_globan_logo', TRUE),
  );
  $form['global']['globan']['cce_basic_config_globan_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link'),
    '#default_value' => variable_get('cce_basic_config_globan_link', TRUE),
  );
  $form['global']['globan']['cce_basic_config_globan_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep the banner sticky on top.'),
    '#default_value' => variable_get('cce_basic_config_globan_mode', TRUE),
  );
  $form['global']['globan']['cce_basic_config_globan_index'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      ' type' => 'number',
    ),
    '#required' => true,
    '#maxlength' => 5,
    '#title' => t('zIndex'),
    '#default_value' => variable_get('cce_basic_config_globan_index', 40),
  );
  return system_settings_form($form);
}