<?php
/**
 * @file
 * wiki_og.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function wiki_og_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'wiki_posts';
  $context->description = 'A context to add active trail class to wiki posts outside community';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'wiki' => 'wiki',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'path' => array(
      'values' => array(
        '~community/*/wiki/*' => '~community/*/wiki/*',
        'community/wiki/*' => 'community/wiki/*',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'links_public',
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to wiki posts outside community');
  t('Menu items');
  $export['wiki_posts'] = $context;

  return $export;
}
