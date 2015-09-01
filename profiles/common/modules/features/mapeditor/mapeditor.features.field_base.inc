<?php
/**
 * @file
 * mapeditor.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function mapeditor_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'mapeditor_csv_data'
  $field_bases['mapeditor_csv_data'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_csv_data',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
  );

  // Exported field_base: 'mapeditor_map_definition'
  $field_bases['mapeditor_map_definition'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'mapeditor_map_definition',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
