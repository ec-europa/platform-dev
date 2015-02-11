<?php
/**
 * @file
 * ec_world_countries.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function ec_world_countries_field_default_fields() {
  $fields = array();

  // Exported field: 'taxonomy_term-ec_world_countries-iso_3166_1_alpha_2_code'.
  $fields['taxonomy_term-ec_world_countries-iso_3166_1_alpha_2_code'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'iso_3166_1_alpha_2_code',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '1',
      'module' => 'text',
      'settings' => array(
        'max_length' => '2',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'ec_world_countries',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '<a href="http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2">ISO 3166-1 alpha-2 codes</a> are two-letter country codes defined in ISO 3166-1, part of the ISO 3166 standard published by the International Organization for Standardization (ISO), to represent countries, dependent territories, and special areas of geographical interest. ',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 0,
        ),
        'mini_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'taxonomy_term',
      'field_name' => 'iso_3166_1_alpha_2_code',
      'label' => 'ISO 3166-1 alpha-2 code',
      'required' => 0,
      'settings' => array(
        'better_formats' => array(
          'allowed_formats' => array(
            'basic_html' => 'basic_html',
            'filtered_html' => 'filtered_html',
            'full_html' => 'full_html',
            'plain_text' => 'plain_text',
          ),
          'allowed_formats_toggle' => 0,
          'default_order_toggle' => 0,
          'default_order_wrapper' => array(
            'formats' => array(
              'basic_html' => array(
                'weight' => '-8',
              ),
              'filtered_html' => array(
                'weight' => '-9',
              ),
              'full_html' => array(
                'weight' => '-10',
              ),
              'plain_text' => array(
                'weight' => '-7',
              ),
            ),
          ),
        ),
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '20',
        ),
        'type' => 'text_textfield',
        'weight' => '-1',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<a href="http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2">ISO 3166-1 alpha-2 codes</a> are two-letter country codes defined in ISO 3166-1, part of the ISO 3166 standard published by the International Organization for Standardization (ISO), to represent countries, dependent territories, and special areas of geographical interest.');
  t('ISO 3166-1 alpha-2 code');

  return $fields;
}
