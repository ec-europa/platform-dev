<?php
/**
 * @file
 * multisite_settings_core.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function multisite_settings_core_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'homepage';
  $context->description = '';
  $context->tag = 'homepage';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-multisite_settings_core-block_1' => array(
          'module' => 'views',
          'delta' => 'multisite_settings_core-block_1',
          'region' => 'content_top',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('homepage');
  $export['homepage'] = $context;

  return $export;
}
