<?php
/**
 * @file
 * multisite_notifications_core.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function multisite_notifications_core_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-pages';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'article' => 'article',
        'page' => 'page',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'multisite_notifications_core-notification_block' => array(
          'module' => 'multisite_notifications_core',
          'delta' => 'notification_block',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['content-pages'] = $context;

  return $export;
}
