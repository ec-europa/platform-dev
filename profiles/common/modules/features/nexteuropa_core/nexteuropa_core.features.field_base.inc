<?php
/**
 * @file
 * nexteuropa_core.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function nexteuropa_core_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ne_body'.
  $field_bases['field_ne_body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ne_body',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 1,
    'type' => 'text_with_summary',
  );

  return $field_bases;
}
