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
  $context->name = 'search';
  $context->description = 'context for search pages';
  $context->tag = 'search';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'search/*' => 'search/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'Facet API: Apache Solr environment: localhost server : Author' => array(
          'module' => 'facetapi',
          'delta' => 'wWWinJ0eOefOtAMbjo2yl86Mnf1rO12j',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'Facet API: Apache Solr environment: localhost server : Content type' => array(
          'module' => 'facetapi',
          'delta' => 'GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('context for search pages');
  t('search');
  $export['search'] = $context;

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
          'region' => 'tools',
          'weight' => 1,
        ),
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
        'print-print-links' => array(
          'module' => 'print',
          'delta' => 'print-links',
          'region' => 'tools_bottom',
          'weight' => '-10',
        ),
        'language' => array(
          'module' => 'locale',
          'delta' => 'language',
          'region' => 'highlighted',
          'weight' => 1,
        ),
        'main-menu' => array(
          'module' => 'system',
          'delta' => 'main-menu',
          'region' => 'featured',
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
