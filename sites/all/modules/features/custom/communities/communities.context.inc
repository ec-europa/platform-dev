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
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'multisite_og_button-og-contextual-links' => array(
          'module' => 'multisite_og_button',
          'delta' => 'og-contextual-links',
          'region' => 'sidebar_first',
          'weight' => '-100',
        ),
        'views-communities_members-block_1' => array(
          'module' => 'views',
          'delta' => 'communities_members-block_1',
          'region' => 'sidebar_first',
          'weight' => '3',
        ),
        'menu-menu-communities-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-communities-menu',
          'region' => 'sidebar_first',
          'weight' => '-99',
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
