<?php

/**
 * @file
 * nexteuropa_newsroom.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function nexteuropa_newsroom_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'newsroom_unpublished_items-blank_source_1-unpublish_node';
  $feeds_tamper->importer = 'newsroom_unpublished_items';
  $feeds_tamper->source = 'Blank source 1';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => '0',
    'only_if_empty' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'unpublish node';
  $export['newsroom_unpublished_items-blank_source_1-unpublish_node'] = $feeds_tamper;

  return $export;
}
