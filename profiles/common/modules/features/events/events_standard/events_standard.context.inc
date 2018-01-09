<?php

/**
 * @file
 * events_standard.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function events_standard_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'even_posts';
  $context->description = 'A context to add active trail class to event posts';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'event' => 'event',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'calendar',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to event posts');
  t('Menu items');
  $export['even_posts'] = $context;

  return $export;
}
