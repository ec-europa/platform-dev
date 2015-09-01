<?php

/**
 * @file
 * Contains forms for the EC geocoder module.
 */

/**
 * Constructs ec_geocoder settings form.
 */
function ec_geocoder_settings() {
  $form = array();
  $form['ec_geocoder_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Geocoder URL'),
    '#default_value' => variable_get('ec_geocoder_url', EC_GEOCODER_URL),
    '#description' => t('URL of the EC corporate geocoder service'),
    '#size' => '60',
  );
  $form['ec_geocoder_minimum_quality'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum quality'),
    '#default_value' => variable_get('ec_geocoder_minimum_quality', EC_GEOCODER_MINIMUM_QUALITY),
    '#description' => t('Minimum quality of geocoder results'),
    '#size' => '12',
  );
  return system_settings_form($form);
}
