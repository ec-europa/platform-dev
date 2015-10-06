<?php
/**
 * @file
 * Multisite Twitter Block Media administration pages.
 */

/**
 * Multisite Twitter Block Media settings.
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

  $vocabularies = _multisite_twitterblock_vocabularies_list();
  $form['fpfis_twitter_feature_settings']['fpfis_twitter_override_vocabularies'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Taxonomy vocabularies'),
    '#options' => $vocabularies,
    '#default_value' => variable_get('fpfis_twitter_override_vocabularies', array()),
    '#description' => t('Taxonomy vocabularies where the common widget settings can be overriden on the taxonomy term edit form.'),
  );

  return system_settings_form($form);
}

/**
 * Provides an array of available vocabularies.
 *
 * @return array
 *   Options list
 */
function _multisite_twitterblock_vocabularies_list() {
  $taxonomy_vocabularies = taxonomy_get_vocabularies();
  $options = array();
  foreach ($taxonomy_vocabularies as $vocabulary) {
    $options[$vocabulary->machine_name] = $vocabulary->name;
  }
  return $options;
}
