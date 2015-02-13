<?php
/**
 * @file
 * ec_world_countries.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ec_world_countries_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'iso_3166_1_alpha_2_code'
  $field_bases['iso_3166_1_alpha_2_code'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
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
    'locked' => 1,
    'module' => 'text',
    'settings' => array(
      'max_length' => 2,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
