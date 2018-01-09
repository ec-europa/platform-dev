<?php

/**
 * @file
 * f_a_q.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function f_a_q_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_faq_categories'.
  $field_bases['field_faq_categories'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_faq_categories',
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => 1,
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'faq_categories',
          'parent' => 0,
        ),
      ),
      'entity_translation_sync' => FALSE,
      'options_list_callback' => 'i18n_taxonomy_allowed_values',
    ),
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  );

  return $field_bases;
}
