<?php

/**
 * @file
 * nexteuropa_newsroom.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function nexteuropa_newsroom_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_deleted_items';
  $feeds_importer->config = array(
    'name' => 'Newsroom Delete Items',
    'description' => 'Deletes items',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
        'auto_scheme' => 'http',
        'accept_invalid_cert' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => 'infsonewsroom:BasicId/text()',
        ),
        'rawXML' => array(
          'xpathparser:0' => 0,
        ),
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => array(
            'xpathparser:0' => 0,
            'context' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'field_newsroom_item_id',
            'unique' => 1,
          ),
        ),
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'newsroom_item',
        'insert_new' => '0',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );

  $export['newsroom_deleted_items'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_unpublished_items';
  $feeds_importer->config = array(
    'name' => 'Newsroom Unpublished Items',
    'description' => 'Unpublish outdated items',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
        'auto_scheme' => 'http',
        'accept_invalid_cert' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => 'infsonewsroom:BasicId/text()',
        ),
        'rawXML' => array(
          'xpathparser:0' => 0,
        ),
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => array(
            'xpathparser:0' => 0,
            'context' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'field_newsroom_item_id',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'Blank source 1',
            'target' => 'status',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'newsroom_item',
        'insert_new' => '0',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );

  $export['newsroom_unpublished_items'] = $feeds_importer;

  return $export;
}
