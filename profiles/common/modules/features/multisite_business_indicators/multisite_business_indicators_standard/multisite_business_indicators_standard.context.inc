<?php

/**
 * @file
 * multisite_business_indicators_standard.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function multisite_business_indicators_standard_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'multisite-business-indicators-standard-overview-page';
  $context->description = '';
  $context->tag = 'reports';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'admin/reports/business-indicators' => 'admin/reports/business-indicators',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-business_indicators_nodes-block' => array(
          'module' => 'views',
          'delta' => 'business_indicators_nodes-block',
          'region' => 'content',
          'weight' => '-25',
        ),
        'views-74c40a5f1bef9d55a8e3702095777832' => array(
          'module' => 'views',
          'delta' => '74c40a5f1bef9d55a8e3702095777832',
          'region' => 'content',
          'weight' => '-24',
        ),
        'views-c99e17fc865c42e99b777b03fbc64ccc' => array(
          'module' => 'views',
          'delta' => 'c99e17fc865c42e99b777b03fbc64ccc',
          'region' => 'content',
          'weight' => '-23',
        ),
        'views-business_indicators_files-block' => array(
          'module' => 'views',
          'delta' => 'business_indicators_files-block',
          'region' => 'content',
          'weight' => '-22',
        ),
        'views-fe2f57b11900f1b46fbf58a4850388cc' => array(
          'module' => 'views',
          'delta' => 'fe2f57b11900f1b46fbf58a4850388cc',
          'region' => 'content',
          'weight' => '-21',
        ),
        'views-5d3c16ed982d9cb46bb4b0cc464a9e4c' => array(
          'module' => 'views',
          'delta' => '5d3c16ed982d9cb46bb4b0cc464a9e4c',
          'region' => 'content',
          'weight' => '-20',
        ),
        'views-6d6433b6fda9f3382f3ae285f260661d' => array(
          'module' => 'views',
          'delta' => '6d6433b6fda9f3382f3ae285f260661d',
          'region' => 'content',
          'weight' => '-19',
        ),
        'views-9d26be1c7bdc1affc0e6844d7f09100f' => array(
          'module' => 'views',
          'delta' => '9d26be1c7bdc1affc0e6844d7f09100f',
          'region' => 'content',
          'weight' => '-18',
        ),
        'views-ccfa5f3b92d0211d8f9f7a3944893240' => array(
          'module' => 'views',
          'delta' => 'ccfa5f3b92d0211d8f9f7a3944893240',
          'region' => 'content',
          'weight' => '-17',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('reports');
  $export['multisite-business-indicators-standard-overview-page'] = $context;

  return $export;
}
