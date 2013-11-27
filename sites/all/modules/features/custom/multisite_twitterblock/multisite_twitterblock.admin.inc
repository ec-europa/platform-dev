<?php
/**
 * @file
 * Horizon 2020 Social Media administration pages.
 */

/**
 * Horizon 2020 Social Media settings.
 */
function multisite_twitterblock_admin_settings() {
  $form = _multisite_twitterblock_settings_form(_multisite_twitterblock_load_twitter_config());

  $form['fpfis_twitter_feature_settings'] = array(
    '#access' => user_access('administer fpfis twitter feature'),
    '#type' => 'fieldset',
    '#title' => t('Feature settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $content_types = node_type_get_names();
  $form['fpfis_twitter_feature_settings']['fpfis_twitter_override_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#options' => $content_types,
    '#default_value' => variable_get('fpfis_twitter_override_types', array()),
    '#description' => t('Content types where the common widget settings can be overriden on the node edit form.'),
  );

  return system_settings_form($form);
}
