<?php
/**
 * @file
 * news_og.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function news_og_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_highlighted'.
  $field_bases['field_highlighted'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_highlighted',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'none',
        1 => 'highlight',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
