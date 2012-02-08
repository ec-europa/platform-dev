<?php
/**
 * @file
 * communities.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function communities_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'communities';
  $context->description = 'context for communities';
  $context->tag = 'communities';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'community' => 'community',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'views' => array(
      'values' => array(
        'communities_directory' => 'communities_directory',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-communities-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-communities-menu',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'views-communities_members-block_1' => array(
          'module' => 'views',
          'delta' => 'communities_members-block_1',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('communities');
  t('context for communities');
  $export['communities'] = $context;

  return $export;
}
