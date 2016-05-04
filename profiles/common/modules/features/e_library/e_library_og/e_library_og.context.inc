<?php
/**
 * @file
 * e_library_og.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function e_library_og_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'document_posts';
  $context->description = 'A context to add active trail class to document posts outside community';
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
    'path' => array(
      'values' => array(
        '~community/*/document/*' => '~community/*/document/*',
        'community/document/*' => 'community/document/*',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'links_public',
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to document posts outside community');
  t('Menu items');
  $export['document_posts'] = $context;

  return $export;
}
