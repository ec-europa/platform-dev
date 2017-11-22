<?php

/**
 * @file
 * survey_standard.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function survey_standard_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'survey_posts';
  $context->description = 'A context to add active trail class to survey posts';
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
        'survey_analysis/*' => 'survey_analysis/*',
        'node/*/webform' => 'node/*/webform',
        'node/*/webform-results' => 'node/*/webform-results',
        'node/*/webform-results/*' => 'node/*/webform-results/*',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'survey',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context to add active trail class to survey posts');
  t('Menu items');
  $export['survey_posts'] = $context;

  return $export;
}
