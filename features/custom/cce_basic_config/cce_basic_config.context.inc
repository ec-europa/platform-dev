<?php
/**
 * @file
 * cce_basic_config.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function cce_basic_config_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'site_wide';
  $context->description = 'global context';
  $context->tag = 'site wide';
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
      'locale-language' => array(
        'module' => 'locale',
        'delta' => 'language',
        'region' => 'highlighted',
        'weight' => '-10',
      ),
      'system-main-menu' => array(
        'module' => 'system',
        'delta' => 'main-menu',
        'region' => 'featured',
        'weight' => '-10',
      ),
    ),
  ),
);
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('global context');
  t('site wide');
  $export['site_wide'] = $context;

  return $export;
}

