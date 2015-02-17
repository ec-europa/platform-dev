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
  $context->description = 'context for the home page';
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
  t('context for the home page');
  t('homepage');
  $export['homepage'] = $context;

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
        'facetapi-odQxTWyhGW1WU7Sl00ISAnQ21BCdJG3A' => array(
          'module' => 'facetapi',
          'delta' => 'odQxTWyhGW1WU7Sl00ISAnQ21BCdJG3A',
          'region' => 'sidebar_left',
          'weight' => '-17',
        ),
        'facetapi-GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu' => array(
          'module' => 'facetapi',
          'delta' => 'GiIy4zr9Gu0ZSa0bumw1Y9qIIpIDf1wu',
          'region' => 'sidebar_left',
          'weight' => '-16',
        ),
        'facetapi-wWWinJ0eOefOtAMbjo2yl86Mnf1rO12j' => array(
          'module' => 'facetapi',
          'delta' => 'wWWinJ0eOefOtAMbjo2yl86Mnf1rO12j',
          'region' => 'sidebar_left',
          'weight' => '-15',
        ),
        'facetapi-8o8kdtP8CKjahDIu1Wy5LGxnDHg3ZYnT' => array(
          'module' => 'facetapi',
          'delta' => '8o8kdtP8CKjahDIu1Wy5LGxnDHg3ZYnT',
          'region' => 'sidebar_left',
          'weight' => '-14',
        ),
        'current_search-standard' => array(
          'module' => 'current_search',
          'delta' => 'standard',
          'region' => 'sidebar_left',
          'weight' => '-10',
        ),
        'apachesolr_search-sort' => array(
          'module' => 'apachesolr_search',
          'delta' => 'sort',
          'region' => 'sidebar_right',
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
        'create-content-button' => array(
          'module' => 'multisite_create_button',
          'delta' => 'create-content-button',
          'region' => 'tools',
          'weight' => '2',
        ),
        'locale-language' => array(
          'module' => 'locale',
          'delta' => 'language',
          'region' => 'header_top',
          'weight' => '-10',
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
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('global context');
  t('site wide');
  $export['site_wide'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'workbench_moderate_all';
  $context->description = '';
  $context->tag = 'workbench';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'admin/workbench/moderate-all*' => 'admin/workbench/moderate-all*',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('workbench');
  $export['workbench_moderate_all'] = $context;

  return $export;
}
