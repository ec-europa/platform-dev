<?php

/**
 * @file
 * nexteuropa_newsroom.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_newsroom_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom';
  $context->description = '';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'newsroom*' => 'newsroom*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-288d683b5a1a8923d17a4d1d68ba2726' => array(
          'module' => 'views',
          'delta' => '288d683b5a1a8923d17a4d1d68ba2726',
          'region' => 'sidebar_left',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('newsroom');
  $export['newsroom'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom_item';
  $context->description = '';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'newsroom_item' => 'newsroom_item',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'nexteuropa_newsroom-newsroom_related_content' => array(
          'module' => 'nexteuropa_newsroom',
          'delta' => 'newsroom_related_content',
          'region' => 'content',
          'weight' => '48',
        ),
        'nexteuropa_newsroom-newsroom_admin_tools' => array(
          'module' => 'nexteuropa_newsroom',
          'delta' => 'newsroom_admin_tools',
          'region' => 'content',
          'weight' => '49',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('newsroom');

  $export['newsroom_item'] = $context;

  return $export;
}
