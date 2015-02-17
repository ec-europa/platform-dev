<?php

/**
 * @file
 * Creates fields and field instances.
 */

/**
 * Creates the 2 letter code field and field instance.
 */
function ec_world_countries_iso_field() {
  $t = get_t();

  // Defines fields for the taxonomy term.
  $array_fields = array(

    // Defines the 2 letter code field.
    'iso_3166_1_alpha_2_code' => array(
      'field_name' => 'iso_3166_1_alpha_2_code',
      'type' => 'text',
      'module' => 'text',
      'active' => '1',
      'cardinality' => '1',
    ),

  );

  // Defines the field instances.
  $array_instances = array(

    // Defines the 2 letter code field instance.
    'iso_3166_1_alpha_2_code' => array(
      'label' => $t('ISO 3166-1 alpha-2 code'),
      'description' => $t('<a href="http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2">ISO 3166-1 alpha-2 codes</a> are two-letter country codes defined in ISO 3166-1, part of the ISO 3166 standard published by the International Organization for Standardization (ISO), to represent countries, dependent territories, and special areas of geographical interest.'),
      'field_name' => 'iso_3166_1_alpha_2_code',
      'required' => TRUE,
      'widget' => array(
        'type' => 'text_textfield',
      ),
      'entity_type' => 'taxonomy_term',
      'bundle' => 'ec_world_countries',
      'weight' => 0,
    ),
  );

  // Creates the fields.
  foreach ($array_fields as $field) {
    field_create_field($field);
  }

  // Creates the field instances.
  foreach ($array_instances as $instance) {
    field_create_instance($instance);
  }

}
