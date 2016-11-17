<?php

/**
 * @file
 * nexteuropa_communities.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_communities_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'communities';
  $context->description = 'Context for communities';
  $context->tag = 'communities';
  $context->conditions = array(
    'context_og_condition_group_node' => array(
      'values' => array(
        2 => 2,
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'context_og_condition_group_type' => array(
      'values' => array(
        'community' => 'community',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'multisite_og_button-og-contextual-links' => array(
          'module' => 'multisite_og_button',
          'delta' => 'og-contextual-links',
          'region' => 'sidebar_left',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Context for communities');
  t('communities');
  $export['communities'] = $context;

  return $export;
}
