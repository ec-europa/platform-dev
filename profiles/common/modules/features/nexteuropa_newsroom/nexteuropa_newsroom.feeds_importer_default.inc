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
    'name' => 'Newsroom Deleted Items',
    'description' => 'Deletes outdated items from the newsroom',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => 'guid/text()',
        ),
        'rawXML' => array(
          'xpathparser:0' => 0,
        ),
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => array(
            'context' => 0,
            'xpathparser:0' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'NewsroomDeleteNodeProcessor',
      'config' => array(
        'content_type' => '',
        'expire' => '-1',
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'newsroom_item',
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
  $feeds_importer->id = 'newsroom_items';
  $feeds_importer->config = array(
    'name' => 'Newsroom Items',
    'description' => 'Imports Newsroom Items from the Newsroom service',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:1' => 'title/text()',
          'xpathparser:2' => 'infsonewsroom:FullContent/text()',
          'xpathparser:3' => 'guid/text()',
          'xpathparser:6' => 'infsonewsroom:ContextContactEmail/text()',
          'xpathparser:7' => 'infsonewsroom:ContextContactText/text()',
          'xpathparser:8' => 'infsonewsroom:BasicDate/text()',
          'xpathparser:9' => 'infsonewsroom:BasictoDate/text()',
          'xpathparser:10' => 'enclosure[@type="image/jpeg"]/@url',
          'xpathparser:11' => 'infsonewsroom:FullLinkedObject/text()',
          'xpathparser:12' => 'infsonewsroom:FullPreTitle/text()',
          'xpathparser:13' => 'infsonewsroom:FullQuoteBox/text()',
          'xpathparser:14' => 'infsonewsroom:BasicRapidPressRelease/text()',
          'xpathparser:15' => 'infsonewsroom:BasicShortTitle/text()',
          'xpathparser:16' => 'infsonewsroom:ContextSpeaker/text() | infsonewsroom:ContextAuthor/text() | infsonewsroom:ContextOrganizer/text()',
          'xpathparser:17' => 'infsonewsroom:ContextVenue/text()',
          'xpathparser:18' => 'infsonewsroom:NewsType/@id',
          'xpathparser:20' => 'category[@domain="Policy" or @domain="Activity" or @domain="Theme" or @domain="Collection" or @domain="Tag"]/text()',
          'xpathparser:24' => 'infsonewsroom:BasicTeaser/text()',
          'xpathparser:26' => 'infsonewsroom:BasicId',
          'xpathparser:27' => 'infsonewsroom:ContextOtherLinkText/text()',
          'xpathparser:28' => 'infsonewsroom:ContextOtherLinkUrl/text()',
          'xpathparser:29' => 'infsonewsroom:BasicUrl/text()',
          'xpathparser:30' => 'enclosure[not(@type="image/jpeg")]/@url',
          'xpathparser:31' => 'enclosure[not(@type="image/jpeg")]/@title',
          'xpathparser:32' => 'infsonewsroom:pubHighlight/text()',
          'xpathparser:33' => 'category/@infsonewsroom:TopicId',
          'xpathparser:34' => 'category[@infsonewsroom:TopicPrimary="1"]/@infsonewsroom:TopicId',
          'xpathparser:35' => 'infsonewsroom:BasicReferenceDate/text()',
          'xpathparser:36' => 'category[@domain="Collection"]/@infsonewsroom:TopicId',
          'xpathparser:37' => 'infsonewsroom:pubIsCentral/text()',
          'xpathparser:38' => 'infsonewsroom:pubIsLong/text()',
          'xpathparser:39' => 'infsonewsroom:pubTeaserOnly/text()',
          'xpathparser:40' => 'infsonewsroom:slave/@guid',
          'xpathparser:41' => 'category[@infsonewsroom:TopicHighlight="1"]/@infsonewsroom:TopicId',
          'xpathparser:42' => 'infsonewsroom:ContextWellknowntext/text()',
          'xpathparser:43' => 'infsonewsroom:ContextProjectName/text()',
          'xpathparser:44' => 'infsonewsroom:ContextProjectAcronym/text()',
          'xpathparser:45' => 'infsonewsroom:ContextProjectURL/text()',
          'xpathparser:46' => 'infsonewsroom:ContextProjectURLDisplay/text()',
          'xpathparser:47' => 'infsonewsroom:ContextProjectCoordinator/text()',
          'xpathparser:48' => 'infsonewsroom:ContextECContent/text()',
          'xpathparser:49' => 'enclosure[@type="image/jpeg"]/@alt',
          'xpathparser:50' => 'enclosure[@type="image/jpeg"]/@title',
          'xpathparser:51' => 'enclosure[@type="image/jpeg"]/@copyright',
          'xpathparser:52' => 'infsonewsroom:BasicDate/text()',
        ),
        'rawXML' => array(
          'xpathparser:1' => 0,
          'xpathparser:2' => 0,
          'xpathparser:3' => 0,
          'xpathparser:6' => 0,
          'xpathparser:7' => 0,
          'xpathparser:8' => 0,
          'xpathparser:9' => 0,
          'xpathparser:10' => 0,
          'xpathparser:11' => 0,
          'xpathparser:12' => 0,
          'xpathparser:13' => 0,
          'xpathparser:14' => 0,
          'xpathparser:15' => 0,
          'xpathparser:16' => 0,
          'xpathparser:17' => 0,
          'xpathparser:18' => 0,
          'xpathparser:20' => 0,
          'xpathparser:24' => 0,
          'xpathparser:26' => 0,
          'xpathparser:27' => 0,
          'xpathparser:28' => 0,
          'xpathparser:29' => 0,
          'xpathparser:30' => 0,
          'xpathparser:31' => 0,
          'xpathparser:32' => 0,
          'xpathparser:33' => 0,
          'xpathparser:34' => 0,
          'xpathparser:35' => 0,
          'xpathparser:36' => 0,
          'xpathparser:37' => 0,
          'xpathparser:38' => 0,
          'xpathparser:39' => 0,
          'xpathparser:40' => 0,
          'xpathparser:41' => 0,
          'xpathparser:42' => 0,
          'xpathparser:43' => 0,
          'xpathparser:44' => 0,
          'xpathparser:45' => 0,
          'xpathparser:46' => 0,
          'xpathparser:47' => 0,
          'xpathparser:48' => 0,
          'xpathparser:49' => 0,
          'xpathparser:50' => 0,
          'xpathparser:51' => 0,
          'xpathparser:52' => 0,
        ),
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => array(
            'context' => 0,
            'xpathparser:1' => 0,
            'xpathparser:2' => 0,
            'xpathparser:3' => 0,
            'xpathparser:6' => 0,
            'xpathparser:7' => 0,
            'xpathparser:8' => 0,
            'xpathparser:9' => 0,
            'xpathparser:10' => 0,
            'xpathparser:11' => 0,
            'xpathparser:12' => 0,
            'xpathparser:13' => 0,
            'xpathparser:14' => 0,
            'xpathparser:15' => 0,
            'xpathparser:16' => 0,
            'xpathparser:17' => 0,
            'xpathparser:18' => 0,
            'xpathparser:20' => 0,
            'xpathparser:24' => 0,
            'xpathparser:26' => 0,
            'xpathparser:27' => 0,
            'xpathparser:28' => 0,
            'xpathparser:29' => 0,
            'xpathparser:30' => 0,
            'xpathparser:31' => 0,
            'xpathparser:32' => 0,
            'xpathparser:33' => 0,
            'xpathparser:34' => 0,
            'xpathparser:35' => 0,
            'xpathparser:36' => 0,
            'xpathparser:37' => 0,
            'xpathparser:38' => 0,
            'xpathparser:39' => 0,
            'xpathparser:40' => 0,
            'xpathparser:41' => 0,
            'xpathparser:42' => 0,
            'xpathparser:43' => 0,
            'xpathparser:44' => 0,
            'xpathparser:45' => 0,
            'xpathparser:46' => 0,
            'xpathparser:47' => 0,
            'xpathparser:48' => 0,
            'xpathparser:49' => 0,
            'xpathparser:50' => 0,
            'xpathparser:51' => 0,
            'xpathparser:52' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'NewsroomFeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '0',
        'authorize' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:1',
            'target' => 'title',
            'unique' => 0,
          ),
          1 => array(
            'source' => 'xpathparser:2',
            'target' => 'body',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'xpathparser:3',
            'target' => 'guid',
            'unique' => 1,
          ),
          3 => array(
            'source' => 'xpathparser:6',
            'target' => 'field_newsroom_item_contact_mail',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'xpathparser:7',
            'target' => 'field_newsroom_item_contact_text',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'xpathparser:8',
            'target' => 'field_newsroom_item_date:start',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'xpathparser:9',
            'target' => 'field_newsroom_item_date:end',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'xpathparser:10',
            'target' => 'field_illustrative_image',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'xpathparser:11',
            'target' => 'field_newsroom_item_linked_obj',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'xpathparser:12',
            'target' => 'field_newsroom_item_pre_title',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'xpathparser:13',
            'target' => 'field_newsroom_item_quote_box',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'xpathparser:14',
            'target' => 'field_newsroom_item_rapid_pr',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'xpathparser:15',
            'target' => 'field_newsroom_item_short_title',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'xpathparser:16',
            'target' => 'field_newsroom_item_speaker',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'xpathparser:17',
            'target' => 'field_newsroom_item_venue',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'xpathparser:18',
            'target' => 'field_newsroom_item_type',
            'term_search' => '1',
            'autocreate' => 0,
          ),
          16 => array(
            'source' => 'xpathparser:20',
            'target' => 'field_tags',
            'term_search' => '0',
            'autocreate' => 0,
          ),
          17 => array(
            'source' => 'xpathparser:24',
            'target' => 'field_teaser',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'xpathparser:26',
            'target' => 'field_newsroom_item_id',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'xpathparser:27',
            'target' => 'field_newsroom_item_other_link:title',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'xpathparser:28',
            'target' => 'field_newsroom_item_other_link:url',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'xpathparser:29',
            'target' => 'field_newsroom_item_main_link:url',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'xpathparser:30',
            'target' => 'field_newsroom_documents:url',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'xpathparser:31',
            'target' => 'field_newsroom_documents:title',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'xpathparser:32',
            'target' => 'promote',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'xpathparser:33',
            'target' => 'field_newsroom_topics',
            'term_search' => '1',
            'autocreate' => 0,
          ),
          26 => array(
            'source' => 'xpathparser:34',
            'target' => 'field_primary_topic',
            'term_search' => '1',
            'autocreate' => 0,
          ),
          27 => array(
            'source' => 'xpathparser:35',
            'target' => 'created',
            'unique' => FALSE,
          ),
          28 => array(
            'source' => 'xpathparser:36',
            'target' => 'field_newsroom_category:etid',
            'unique' => FALSE,
          ),
          29 => array(
            'source' => 'xpathparser:37',
            'target' => 'sticky',
            'unique' => FALSE,
          ),
          30 => array(
            'source' => 'xpathparser:38',
            'target' => 'field_newsroom_short_item',
            'unique' => FALSE,
          ),
          31 => array(
            'source' => 'xpathparser:39',
            'target' => 'field_newsroom_teaser_only',
            'unique' => FALSE,
          ),
          32 => array(
            'source' => 'xpathparser:40',
            'target' => 'field_related_content',
            'unique' => FALSE,
          ),
          33 => array(
            'source' => 'xpathparser:41',
            'target' => 'field_highlighted_newsroom_topic',
            'term_search' => '1',
            'autocreate' => 0,
          ),
          34 => array(
            'source' => 'xpathparser:42',
            'target' => 'field_newsroom_location:wkt',
            'unique' => FALSE,
          ),
          35 => array(
            'source' => 'xpathparser:43',
            'target' => 'field_newsroom_project',
            'unique' => FALSE,
          ),
          36 => array(
            'source' => 'xpathparser:44',
            'target' => 'field_newsroom_project_acr',
            'unique' => FALSE,
          ),
          37 => array(
            'source' => 'xpathparser:45',
            'target' => 'field_newsroom_project_website:url',
            'unique' => FALSE,
          ),
          38 => array(
            'source' => 'xpathparser:46',
            'target' => 'field_newsroom_project_website:title',
            'unique' => FALSE,
          ),
          39 => array(
            'source' => 'xpathparser:47',
            'target' => 'field_nr_project_coordinator',
            'unique' => FALSE,
          ),
          40 => array(
            'source' => 'xpathparser:48',
            'target' => 'field_newsroom_ec_content',
            'unique' => FALSE,
          ),
          41 => array(
            'source' => 'xpathparser:49',
            'target' => 'field_file_image_alt_text',
            'unique' => FALSE,
          ),
          42 => array(
            'source' => 'xpathparser:50',
            'target' => 'field_file_image_title_text',
            'unique' => FALSE,
          ),
          43 => array(
            'source' => 'xpathparser:51',
            'target' => 'field_newsroom_copyrights',
            'unique' => FALSE,
          ),
          44 => array(
            'source' => 'xpathparser:52',
            'target' => 'created',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'full_html',
        'skip_hash_check' => 1,
        'bundle' => 'newsroom_item',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['newsroom_items'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_services';
  $feeds_importer->config = array(
    'name' => 'Newsroom Services',
    'description' => 'Imports Services from the Newsroom service.',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => 'guid/text()',
          'xpathparser:1' => 'infsonewsroom:BasicSvId/text()',
          'xpathparser:2' => 'title/text()',
          'xpathparser:3' => 'category[@domain="Subchapter"]/@infsonewsroom:TopicId',
          'xpathparser:4' => 'infsonewsroom:BasicSvStatus/text()',
          'xpathparser:5' => 'infsonewsroom:BasicSvType/text()',
        ),
        'rawXML' => array(
          'xpathparser:0' => 0,
          'xpathparser:1' => 0,
          'xpathparser:2' => 0,
          'xpathparser:3' => 0,
          'xpathparser:4' => 0,
          'xpathparser:5' => 0,
        ),
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => array(
            'context' => 0,
            'xpathparser:0' => 0,
            'xpathparser:1' => 0,
            'xpathparser:2' => 0,
            'xpathparser:3' => 0,
            'xpathparser:4' => 0,
            'xpathparser:5' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 'newsroom_service',
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'xpathparser:1',
            'target' => 'field_newsroom_service_id',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'xpathparser:2',
            'target' => 'name',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'xpathparser:3',
            'target' => 'field_newsroom_topic',
            'term_search' => '1',
            'autocreate' => 0,
          ),
          4 => array(
            'source' => 'xpathparser:4',
            'target' => 'field_service_active',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'xpathparser:5',
            'target' => 'field_service_type',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 1,
        'bundle' => 'newsroom_service',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '10800',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['newsroom_services'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_topics';
  $feeds_importer->config = array(
    'name' => 'Newsroom Topics',
    'description' => 'Imports Topics from the Newsroom service',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => '@infsonewsroom:TopicId',
          'xpathparser:1' => '@infsonewsroom:TopicId',
          'xpathparser:2' => 'text()',
          'xpathparser:3' => '@domain',
          'xpathparser:4' => '@infsonewsroom:parentTopicId',
        ),
        'rawXML' => array(
          'xpathparser:0' => 0,
          'xpathparser:1' => 0,
          'xpathparser:2' => 0,
          'xpathparser:3' => 0,
          'xpathparser:4' => 0,
        ),
        'context' => '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter"]',
        'exp' => array(
          'errors' => 1,
          'debug' => array(
            'context' => 0,
            'xpathparser:0' => 0,
            'xpathparser:1' => 0,
            'xpathparser:2' => 0,
            'xpathparser:3' => 0,
            'xpathparser:4' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'xpathparser:1',
            'target' => 'field_newsroom_topic_id',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'xpathparser:2',
            'target' => 'name',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'xpathparser:3',
            'target' => 'field_newsroom_category_domain',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'xpathparser:4',
            'target' => 'parentguid',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 1,
        'bundle' => 'newsroom_topic',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['newsroom_topics'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_type';
  $feeds_importer->config = array(
    'name' => 'Newsroom Type',
    'description' => 'Imports Item Types from the Newsroom service.',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => 'infsonewsroom:BasicTypeId/text()',
          'xpathparser:1' => 'infsonewsroom:BasicTypeId/text()',
          'xpathparser:2' => 'infsonewsroom:BasicMetaTypeName/text()',
          'xpathparser:3' => 'title/text()',
          'xpathparser:4' => 'infsonewsroom:BasicTypeParent/text()',
        ),
        'rawXML' => array(
          'xpathparser:0' => 'xpathparser:0',
          'xpathparser:4' => 'xpathparser:4',
          'xpathparser:1' => 0,
          'xpathparser:2' => 0,
          'xpathparser:3' => 0,
        ),
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => array(
            'context' => 0,
            'xpathparser:0' => 0,
            'xpathparser:1' => 0,
            'xpathparser:2' => 0,
            'xpathparser:3' => 0,
            'xpathparser:4' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 'newsroom_item_type',
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'xpathparser:1',
            'target' => 'field_newsroom_type_id',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'xpathparser:2',
            'target' => 'field_newsroom_import_name',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'xpathparser:3',
            'target' => 'name',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'xpathparser:4',
            'target' => 'parentguid',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 1,
        'bundle' => 'newsroom_item_type',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['newsroom_type'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_unpublished_items';
  $feeds_importer->config = array(
    'name' => 'Newsroom Unpublished Items',
    'description' => 'Deletes unpublished items from the newsroom',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => 'guid/text()',
        ),
        'rawXML' => array(
          'xpathparser:0' => 0,
        ),
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => array(
            'context' => 0,
            'xpathparser:0' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'NewsroomDeleteNodeProcessor',
      'config' => array(
        'content_type' => '',
        'expire' => '-1',
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'newsroom_item',
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
