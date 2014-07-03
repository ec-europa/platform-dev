<?php
/**
 * @file
 * newsletters.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function newsletters_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsletters_posts';
  $context->description = 'A context to add active trail class to newsletter posts';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'simplenews' => 'simplenews',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'my_subscriptions',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to newsletter posts');
  t('Menu items');
  $export['newsletters_posts'] = $context;

  return $export;
}
