<?php

/**
 * @file
 * newsletters.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function newsletters_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_related_contents'.
  $field_bases['field_related_contents'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_related_contents',
    'foreign keys' => array(
      'node' => array(
        'columns' => array(
          'target_id' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 1,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'direction' => 'ASC',
          'field' => 'body:value',
          'property' => 'nid',
          'type' => 'none',
        ),
        'target_bundles' => array(
          'article' => 'article',
          'page' => 'page',
        ),
      ),
      'handler_submit' => 'Change handler',
      'referenceable_types' => array(
        'article' => 'article',
        'page' => 'page',
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
