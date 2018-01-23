<?php

/**
 * @file
 * Edee.context.inc.
 */

/**
 * Implements hook_context_default_contexts().
 */
function events_og_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'event_posts';
  $context->description = 'A context to add active trail class to event posts outside community';
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
    'path' => array(
      'values' => array(
        '~community/*/event/*' => '~community/*/event/*',
        'community/event/*' => 'community/event/*',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'events_public',
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to links posts outside community');
  t('Menu items');
  $export['event_posts'] = $context;

  return $export;
}
