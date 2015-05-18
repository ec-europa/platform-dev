<?php
/**
 * @file
 * e_library_standard.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function e_library_standard_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'document_posts';
  $context->description = 'A context to add active trail class to document posts';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'document' => 'document',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'e_library',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to document posts');
  t('Menu items');
  $export['document_posts'] = $context;

  return $export;
}
