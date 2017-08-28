<?php

/**
 * @file
 * Multisite organic group navigation tree settings.
 *
 * Vocabulary is automatically set on install but can be changed.
 */

/**
 * Form builder for the OG Navigation Tree settings form.
 */
function multisite_og_navigation_tree_settings($form) {
  $form = array();

  $vocabularies = taxonomy_get_vocabularies();
  $options = array('' => '--------------');
  foreach ($vocabularies as $tid => $vocabulary) {
    $options[$tid] = i18n_taxonomy_vocabulary_name($vocabulary);
  }

  $entities = og_get_all_group_entity();
  $group_types = array();
  foreach ($entities as $key => $value) {
    $entity = entity_get_info($key);
    $bundles = $entity['bundles'];
    foreach ($bundles as $bundle_name => $bundle) {
      if (og_is_group_type($key, $bundle_name)) {
        $group_types[$bundle_name] = $entity;
      }
    }
  }

  $form['multisite_og_navigation_tree_vid'] = array(
    '#type' => 'select',
    '#title' => t('Group taxonomy'),
    '#options' => $options,
    '#default_value' => variable_get('multisite_og_navigation_tree_vid', array()),
    '#description' => t("do not change this if you don't know what you are doing"),
  );

  if (variable_get('multisite_og_navigation_tree_vid', array())) {
    $form['multisite_og_navigation_tree_mont_taxonomy_enabled'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Enable Group taxonomy'),
      '#options' => drupal_map_assoc(array_keys($group_types)),
      '#default_value' => variable_get('multisite_og_navigation_tree_mont_taxonomy_enabled', array()),
      '#description' => t("do not change this if you don't know what you are doing"),
    );
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save settings'));
  return $form;
}

/**
 * Submit handler for the OG Navigation Tree settings form.
 *
 * @see multisite_og_navigation_tree_settings()
 */
function multisite_og_navigation_tree_settings_submit($form, $form_state) {
  variable_set('multisite_og_navigation_tree_mont_taxonomy_enabled', array_filter($form_state['values']['multisite_og_navigation_tree_mont_taxonomy_enabled']));
  variable_set('multisite_og_navigation_tree_vid', $form_state['values']['multisite_og_navigation_tree_vid']);
}
