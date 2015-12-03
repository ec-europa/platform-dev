<?php
/**
 * @file
 * nexteuropa_newsroom.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_newsroom_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom';
  $context->description = '';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'newsroom' => 'newsroom',
        'newsroom_calendar' => 'newsroom_calendar',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-newsroom_navigation-type' => array(
          'module' => 'views',
          'delta' => 'newsroom_navigation-type',
          'region' => 'sidebar_left',
          'weight' => '-9',
        ),
        'views-39a3f985e3441350bd00477b466722e0' => array(
          'module' => 'views',
          'delta' => '39a3f985e3441350bd00477b466722e0',
          'region' => 'sidebar_left',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('newsroom');
  $export['newsroom'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom_item';
  $context->description = '';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'newsroom_item' => 'newsroom_item',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'newsroom-newsroom_admin_tools' => array(
          'module' => 'newsroom',
          'delta' => 'newsroom_admin_tools',
          'region' => 'content',
          'weight' => '2',
        ),
        'views-newsroom_related_content-block' => array(
          'module' => 'views',
          'delta' => 'newsroom_related_content-block',
          'region' => 'content',
          'weight' => '1',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('newsroom');
  $export['newsroom_item'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'newsroom_site_wide';
  $context->description = '';
  $context->tag = 'newsroom';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~homepage' => '~homepage',
        'site_wide' => 'site_wide',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'newsroom-newsroom_newsletter_subscription' => array(
          'module' => 'newsroom',
          'delta' => 'newsroom_newsletter_subscription',
          'region' => 'sidebar_right',
          'weight' => '-10',
        ),
        'newsroom-newsroom_topic_summary' => array(
          'module' => 'newsroom',
          'delta' => 'newsroom_topic_summary',
          'region' => 'content',
          'weight' => '1',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('newsroom');
  $export['newsroom_site_wide'] = $context;

  return $export;
}
