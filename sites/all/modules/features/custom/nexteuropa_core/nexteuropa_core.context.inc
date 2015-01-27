<?php
/**
 * @file
 * nexteuropa_core.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_core_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'core-administrative-section';
  $context->description = '';
  $context->tag = 'Sections';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'user' => 'user',
        'user/*' => 'user/*',
        'user/*/*' => 'user/*/*',
        'user/*/*/*' => 'user/*/*/*',
        'user/*/*/*/*' => 'user/*/*/*/*',
        'admin' => 'admin',
        'admin/*' => 'admin/*',
        'admin/*/*' => 'admin/*/*',
        'admin/*/*/*' => 'admin/*/*/*',
        'admin/*/*/*/*' => 'admin/*/*/*/*',
        'admin/*/*/*/*/*' => 'admin/*/*/*/*/*',
        'admin/*/*/*/*/*/*' => 'admin/*/*/*/*/*/*',
        'admin/*/*/*/*/*/*/*' => 'admin/*/*/*/*/*/*/*',
        'node/add' => 'node/add',
        'node/*/*' => 'node/*/*',
        'node/*/*/*' => 'node/*/*/*',
        'node/*/*/*/*' => 'node/*/*/*/*',
        'node/*/*/*/*/*' => 'node/*/*/*/*/*',
        'node/*/*/*/*/*/*' => 'node/*/*/*/*/*/*',
        'block/*' => 'block/*',
        'block/*/*' => 'block/*/*',
        'block/*/*/*' => 'block/*/*/*',
        'block/*/*/*/*' => 'block/*/*/*/*',
        'block/*/*/*/*/*' => 'block/*/*/*/*/*',
        'block/*/*/*/*/*/*' => 'block/*/*/*/*/*/*',
        'taxonomy/term/*' => 'taxonomy/term/*',
        'taxonomy/term/*/*' => 'taxonomy/term/*/*',
        'taxonomy/term/*/*/*' => 'taxonomy/term/*/*/*',
        'taxonomy/term/*/*/*/*' => 'taxonomy/term/*/*/*/*',
        'file' => 'file',
        'file/*' => 'file/*',
        'file/*/*' => 'file/*/*',
        'file/*/*/*' => 'file/*/*/*',
      ),
    ),
    'user' => array(
      'values' => array(
        'authenticated user' => 'authenticated user',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Sections');
  $export['core-administrative-section'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'core-front';
  $context->description = '';
  $context->tag = 'Front page';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Front page');
  $export['core-front'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'core-sitewide';
  $context->description = '';
  $context->tag = 'Sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'easy_breadcrumb-easy_breadcrumb' => array(
          'module' => 'easy_breadcrumb',
          'delta' => 'easy_breadcrumb',
          'region' => 'header_bottom',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Sitewide');
  $export['core-sitewide'] = $context;

  return $export;
}
