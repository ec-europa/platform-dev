<?php
/**
 * @file
 * links.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function links_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'links';
  $context->description = 'Context for links in communities';
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
        'links-Add-links-block' => array(
          'module' => 'links',
          'delta' => 'Add-links-block',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'views-links-block' => array(
          'module' => 'views',
          'delta' => 'links-block',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Context for links in communities');
  t('communities');
  $export['links'] = $context;

  return $export;
}
