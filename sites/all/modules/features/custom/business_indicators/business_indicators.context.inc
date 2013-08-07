<?php
/**
 * @file
 * business_indicators.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function business_indicators_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'business-indicators-overview-page';
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
        'views-74c40a5f1bef9d55a8e3702095777832' => array(
          'module' => 'views',
          'delta' => '74c40a5f1bef9d55a8e3702095777832',
          'region' => 'content',
          'weight' => '-31',
        ),
        'views-business_indicators_nodes-block' => array(
          'module' => 'views',
          'delta' => 'business_indicators_nodes-block',
          'region' => 'content',
          'weight' => '-31',
        ),
        'views-c99e17fc865c42e99b777b03fbc64ccc' => array(
          'module' => 'views',
          'delta' => 'c99e17fc865c42e99b777b03fbc64ccc',
          'region' => 'content',
          'weight' => '-30',
        ),
        'views-business_indicators_files-block' => array(
          'module' => 'views',
          'delta' => 'business_indicators_files-block',
          'region' => 'content',
          'weight' => '-29',
        ),
        'views-fe2f57b11900f1b46fbf58a4850388cc' => array(
          'module' => 'views',
          'delta' => 'fe2f57b11900f1b46fbf58a4850388cc',
          'region' => 'content',
          'weight' => '-28',
        ),
        'views-5d3c16ed982d9cb46bb4b0cc464a9e4c' => array(
          'module' => 'views',
          'delta' => '5d3c16ed982d9cb46bb4b0cc464a9e4c',
          'region' => 'content',
          'weight' => '-27',
        ),
        'views-6d6433b6fda9f3382f3ae285f260661d' => array(
          'module' => 'views',
          'delta' => '6d6433b6fda9f3382f3ae285f260661d',
          'region' => 'content',
          'weight' => '-26',
        ),
        'views-9d26be1c7bdc1affc0e6844d7f09100f' => array(
          'module' => 'views',
          'delta' => '9d26be1c7bdc1affc0e6844d7f09100f',
          'region' => 'content',
          'weight' => '-24',
        ),
        'views-3ee8c29ea058b303b8ae2c2845791876' => array(
          'module' => 'views',
          'delta' => '3ee8c29ea058b303b8ae2c2845791876',
          'region' => 'content',
          'weight' => '-23',
        ),
        'views-f60be8b503a8fc099437066f49314f51' => array(
          'module' => 'views',
          'delta' => 'f60be8b503a8fc099437066f49314f51',
          'region' => 'content',
          'weight' => '-22',
        ),
        'views-3cfdbe36c55c508ec864fa3ad7bcb8e6' => array(
          'module' => 'views',
          'delta' => '3cfdbe36c55c508ec864fa3ad7bcb8e6',
          'region' => 'content',
          'weight' => '-21',
        ),
        'views-28b0d2df4dd673328e69d4f5de8caafe' => array(
          'module' => 'views',
          'delta' => '28b0d2df4dd673328e69d4f5de8caafe',
          'region' => 'content',
          'weight' => '-20',
        ),
        'views-b53a1452b65ee68791642413d64afd6d' => array(
          'module' => 'views',
          'delta' => 'b53a1452b65ee68791642413d64afd6d',
          'region' => 'content',
          'weight' => '-19',
        ),
        'views-ceeedca22b229b81feeb1578018a0263' => array(
          'module' => 'views',
          'delta' => 'ceeedca22b229b81feeb1578018a0263',
          'region' => 'content',
          'weight' => '-18',
        ),
        'views-f2af970842b81ed3ab7adbd1053bdb63' => array(
          'module' => 'views',
          'delta' => 'f2af970842b81ed3ab7adbd1053bdb63',
          'region' => 'content',
          'weight' => '-17',
        ),
        'views-d3dc753b2b6af8d89b66f13c1f41a0e7' => array(
          'module' => 'views',
          'delta' => 'd3dc753b2b6af8d89b66f13c1f41a0e7',
          'region' => 'content',
          'weight' => '-16',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('reports');
  $export['business-indicators-overview-page'] = $context;

  return $export;
}
