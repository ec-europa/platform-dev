<?php
/**
 * @file
 * nexteuropa_event.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_event_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'event_ical';
  $context->description = 'Context for events';
  $context->tag = 'Events';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'nexteuropa_event' => 'nexteuropa_event',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-ical-block' => array(
          'module' => 'views',
          'delta' => 'ical-block',
          'region' => 'content_bottom',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Context for events');
  t('Events');
  $export['event_ical'] = $context;

  return $export;
}
