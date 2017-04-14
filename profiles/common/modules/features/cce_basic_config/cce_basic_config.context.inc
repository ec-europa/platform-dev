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

  $context = new stdClass();
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
        'user-menu' => array(
          'module' => 'system',
          'delta' => 'user-menu',
          'region' => 'utility',
          'weight' => 1,
        ),
        'create-content-button' => array(
          'module' => 'multisite_create_button',
          'delta' => 'create-content-button',
          'region' => 'tools',
          'weight' => '2',
        ),
        'system-main-menu' => array(
          'module' => 'system',
          'delta' => 'main-menu',
          'region' => 'featured',
          'weight' => '-10',
        ),
        'easy_breadcrumb-easy_breadcrumb' => array(
          'module' => 'easy_breadcrumb',
          'delta' => 'easy_breadcrumb',
          'region' => 'featured',
          'weight' => '-11',
        ),
        'print-print-links' => array(
          'module' => 'print',
          'delta' => 'print-links',
          'region' => 'content_bottom',
          'weight' => '-10',
        ),
        'form' => array(
          'module' => 'search',
          'delta' => 'form',
          'region' => 'header_right',
          'weight' => 1,
        ),
        'footer' => array(
          'module' => 'cce_basic_config',
          'delta' => 'footer_ipg',
          'region' => 'footer',
          'weight' => 1,
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
