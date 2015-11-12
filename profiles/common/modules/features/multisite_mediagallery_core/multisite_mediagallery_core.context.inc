<?php
/**
 * @file
 * multisite_mediagallery_core.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function multisite_mediagallery_core_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'gallery_posts';
  $context->description = 'A context to add active trail class to gallery posts';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'gallerymedia' => 'gallerymedia',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'galleries',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to gallery posts');
  t('Menu items');
  $export['gallery_posts'] = $context;

  return $export;
}
