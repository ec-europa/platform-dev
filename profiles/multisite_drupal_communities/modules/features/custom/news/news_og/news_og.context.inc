<?php
/**
 * @file
 * news_og.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function news_og_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'community_homepage';
  $context->description = 'Display on community homepage';
  $context->tag = 'communities';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'community' => 'community',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-news-block_2' => array(
          'module' => 'views',
          'delta' => 'news-block_2',
          'region' => 'content_top',
          'weight' => '9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display on community homepage');
  t('communities');
  $export['community_homepage'] = $context;

  return $export;
}
