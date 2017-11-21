<?php

/**
 * @file
 * nexteuropa_mediagallery.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function nexteuropa_mediagallery_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_media_upload'.
  $field_bases['field_media_upload'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_media_upload',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 1,
    'module' => 'mediafield',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'media',
  );

  return $field_bases;
}
