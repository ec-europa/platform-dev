<?php
/**
 * @file
 * cce_basic_config.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function STARTERKIT_field_default_fields() {
  $fields = array();

  // Exported field: 'comment-comment_node_article-comment_body'.
  $fields['STARTERKIT_CUSTOM_FIELD'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'STARTERKIT_entity_type',
      ),
      'field_name' => 'STARTERKIT_field_name',
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
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'STARTERKIT_CUSTOM_BUNDLE',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'STARTERKIT_entity_type',
      'field_name' => 'STARTERKIT_field_name',
      'label' => 'STARTERKIT_field_label',
      'required' => TRUE,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'text',
        'settings' => array(
          'rows' => 5,
        ),
        'type' => 'text_textarea',
        'weight' => 0,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('STARTERKIT_CUSTOM_STRINGS');


  return $fields;
}
