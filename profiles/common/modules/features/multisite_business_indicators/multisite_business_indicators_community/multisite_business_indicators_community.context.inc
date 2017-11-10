<?php

/**
 * @file
 * multisite_business_indicators_community.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function multisite_business_indicators_community_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'multisite-business-indicators-community-overview-page';
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
        'views-1045fea629349cc121571e7d865e7c40' => array(
          'module' => 'views',
          'delta' => '1045fea629349cc121571e7d865e7c40',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('reports');
  $export['multisite-business-indicators-community-overview-page'] = $context;

  return $export;
}
