<?php
/**
 * @file
 * news_core.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function news_core_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'news_posts';
  $context->description = 'A context to add active trail class to news posts';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'news' => 'news',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'news',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to news posts');
  t('Menu items');
  $export['news_posts'] = $context;

  return $export;
}
