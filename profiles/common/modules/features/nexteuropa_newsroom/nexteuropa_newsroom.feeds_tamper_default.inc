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
  $feeds_tamper->id = 'newsroom_items-xpathparser_38-convert_boolean';
  $feeds_tamper->importer = 'newsroom_items';
  $feeds_tamper->source = 'xpathparser:38';
  $feeds_tamper->plugin_id = 'convert_boolean';
  $feeds_tamper->settings = array(
    'true_value' => '1',
    'false_value' => '0',
    'match_case' => 0,
    'no_match' => 'true',
    'other_text' => '',
    'no_match_value' => TRUE,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Convert to boolean';
  $export['newsroom_items-xpathparser_38-convert_boolean'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'newsroom_items-xpathparser_39-convert_boolean';
  $feeds_tamper->importer = 'newsroom_items';
  $feeds_tamper->source = 'xpathparser:39';
  $feeds_tamper->plugin_id = 'convert_boolean';
  $feeds_tamper->settings = array(
    'true_value' => '1',
    'false_value' => '0',
    'match_case' => 0,
    'no_match' => 'false',
    'other_text' => '',
    'no_match_value' => FALSE,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Convert to boolean';
  $export['newsroom_items-xpathparser_39-convert_boolean'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'newsroom_topics-xpathparser_0-rewrite';
  $feeds_tamper->importer = 'newsroom_topics';
  $feeds_tamper->source = 'xpathparser:0';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => 'newsroom_topic-[xpathparser:0]',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Rewrite';
  $export['newsroom_topics-xpathparser_0-rewrite'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'newsroom_topics-xpathparser_4-rewrite';
  $feeds_tamper->importer = 'newsroom_topics';
  $feeds_tamper->source = 'xpathparser:4';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => 'newsroom_topic-[xpathparser:4]',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Rewrite';
  $export['newsroom_topics-xpathparser_4-rewrite'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'newsroom_type-xpathparser_0-rewrite';
  $feeds_tamper->importer = 'newsroom_type';
  $feeds_tamper->source = 'xpathparser:0';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => 'newsroom_type-[xpathparser:0]',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Rewrite';
  $export['newsroom_type-xpathparser_0-rewrite'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'newsroom_items_multilingual-blank_source_1-default_value';
  $feeds_tamper->importer = 'newsroom_items_multilingual';
  $feeds_tamper->source = 'Blank source 1';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'en',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set default language';
  $export['newsroom_items_multilingual-blank_source_1-default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'newsroom_type-xpathparser_4-rewrite';
  $feeds_tamper->importer = 'newsroom_type';
  $feeds_tamper->source = 'xpathparser:4';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => 'newsroom_type-[xpathparser:4]',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Rewrite';
  $export['newsroom_type-xpathparser_4-rewrite'] = $feeds_tamper;

  return $export;
}
