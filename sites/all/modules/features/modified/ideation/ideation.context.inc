<?php
/**
 * @file
 * ideation.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ideation_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'ideas_listing';
  $context->description = '';
  $context->tag = 'ideas';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'idea_site' => 'idea_site',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'views' => array(
      'values' => array(
        'ideas_listing' => 'ideas_listing',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'ideation-ideation_box' => array(
          'module' => 'ideation',
          'delta' => 'ideation_box',
          'region' => 'content_top',
          'weight' => '-16',
        ),
        'views-4fc346cc5920b0b8027cf39c18f31cb1' => array(
          'module' => 'views',
          'delta' => '4fc346cc5920b0b8027cf39c18f31cb1',
          'region' => 'content_top',
          'weight' => '-15',
        ),
        'views-5996f5cc8467b404a194242c0f6379a8' => array(
          'module' => 'views',
          'delta' => '5996f5cc8467b404a194242c0f6379a8',
          'region' => 'content_top',
          'weight' => '-14',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ideas');
  $export['ideas_listing'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'ideas_main_listing';
  $context->description = 'Display callout box on main listing.';
  $context->tag = 'ideas';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'ideas_listing' => 'ideas_listing',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'ideation-ideation_box' => array(
          'module' => 'ideation',
          'delta' => 'ideation_box',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display callout box on main listing.');
  t('ideas');
  $export['ideas_main_listing'] = $context;

  return $export;
}
