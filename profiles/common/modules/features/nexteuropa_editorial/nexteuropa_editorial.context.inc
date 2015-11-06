<?php
/**
 * @file
 * nexteuropa_editorial.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_editorial_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'editorial-administrative-section';
  $context->description = '';
  $context->tag = 'Sections';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'editorial_team' => 'editorial_team',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'path' => array(
      'values' => array(
        'group/node/*' => 'group/node/*',
        'group/node/*/*' => 'group/node/*/*',
        'group/node/*/*/*' => 'group/node/*/*/*',
        'group/node/*/*/*/*' => 'group/node/*/*/*/*',
        'group/node/*/*/*/*/*' => 'group/node/*/*/*/*/*',
        'node/*/*' => 'node/*/*',
        'node/*/*/*' => 'node/*/*/*',
        'node/*/*/*/*' => 'node/*/*/*/*',
        'node/*/*/*/*/*' => 'node/*/*/*/*/*',
        'node/*/*/*/*/*/*' => 'node/*/*/*/*/*/*',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Sections');
  $export['editorial-administrative-section'] = $context;

  return $export;
}
