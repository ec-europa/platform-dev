<?php

/**
 * @file
 * survey_og.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function survey_og_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'survey_posts';
  $context->description = 'A context to add active trail class to survey posts outside community';
  $context->tag = 'Menu items';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'webform' => 'webform',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'path' => array(
      'values' => array(
        '~community/*/links/*' => '~community/*/survey/*',
        'community/links/*' => 'community/survey/*',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'survey_public',
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to survey posts outside community');
  t('Menu items');
  $export['survey_posts'] = $context;

  return $export;
}
