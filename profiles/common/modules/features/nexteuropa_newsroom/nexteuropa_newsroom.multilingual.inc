<?php

/**
 * @file
 * Nexteuropa_newsroom.multilingual.inc.
 */

/**
 * Import the multilingual importer.
 */
function _nexteuropa_newsroom_create_multilingual_items_importer() {
  $def_lang = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'title' => array(
      'query' => 'title[@lang="' . $def_lang . '"]/text()',
    ),
    'title_field' => array(
      'query' => 'title',
    ),
    'guid' => array(
      'query' => 'guid/text()',
      'unique' => 1,
    ),
    'field_newsroom_item_date:start' => array(
      'query' => 'infsonewsroom:BasicDate/text()',
    ),
    'field_newsroom_item_date:end' => array(
      'query' => 'infsonewsroom:BasictoDate/text()',
    ),
    'field_illustrative_image' => array(
      'query' => 'enclosure[@type="image/jpeg"]/@url',
    ),
    'field_illustrative_image:title' => array(
      'query' => 'infsonewsroom:PicTitle',
    ),
    'field_illustrative_image:alt' => array(
      'query' => 'infsonewsroom:PicAlt',
    ),
    'field_illustrative_image:copyright' => array(
      'query' => 'infsonewsroom:PicCopyright',
    ),
    'field_illustrative_image:caption' => array(
      'query' => 'infsonewsroom:PicCaption',
    ),
    'field_newsroom_item_rapid_pr' => array(
      'query' => 'infsonewsroom:BasicRapidPressRelease/text()',
    ),
    'field_newsroom_item_type' => array(
      'query' => 'infsonewsroom:NewsType/@id',
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => TRUE,
      'vocabulary' => 'newsroom_item_type',
      'field' => 'field_newsroom_type_id',
    ),
    'field_tags' => array(
      'query' => 'category[@domain="Policy" or @domain="Activity" or @domain="Theme" or @domain="Collection" or @domain="Tag"]/text()',
      'options' => array(
        'term_search' => '0',
        'autocreate' => 0,
      ),
    ),
    'field_newsroom_item_id' => array(
      'query' => 'infsonewsroom:BasicId',
    ),
    'field_newsroom_item_other_link:title' => array(
      'query' => 'infsonewsroom:ContextOtherLinkText',
    ),
    'field_newsroom_item_other_link:url' => array(
      'query' => 'infsonewsroom:ContextOtherLinkUrl',
    ),
    'field_newsroom_item_main_link:url' => array(
      'query' => 'infsonewsroom:BasicUrl',
    ),
    'field_newsroom_documents:url' => array(
      'query' => 'enclosure[not(@type="image/jpeg")]/@url',
    ),
    'field_newsroom_documents:title' => array(
      'query' => 'enclosure[not(@type="image/jpeg")]/@title',
    ),
    'promote' => array(
      'query' => 'infsonewsroom:pubHighlight/text()',
    ),
    'field_newsroom_topics' => array(
      'query' => 'category/@infsonewsroom:TopicId',
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => TRUE,
      'vocabulary' => 'newsroom_topic',
      'field' => 'field_newsroom_topic_id',
    ),
    'field_primary_topic' => array(
      'query' => 'category[@infsonewsroom:TopicPrimary="1"]/@infsonewsroom:TopicId',
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => TRUE,
      'vocabulary' => 'newsroom_topic',
      'field' => 'field_newsroom_topic_id',
    ),
    'created' => array(
      'query' => 'infsonewsroom:BasicReferenceDate/text()',
    ),
    'field_newsroom_category:etid' => array(
      'query' => 'category[@domain="Collection"]/@infsonewsroom:TopicId',
    ),
    'sticky' => array(
      'query' => 'infsonewsroom:pubIsCentral/text()',
    ),
    'field_newsroom_short_item' => array(
      'query' => 'infsonewsroom:pubIsLong/text()',
    ),
    'field_newsroom_teaser_only' => array(
      'query' => 'infsonewsroom:pubTeaserOnly/text()',
    ),
    'field_related_content' => array(
      'query' => 'infsonewsroom:slave/@guid',
    ),
    'field_newsroom_project_acr' => array(
      'query' => 'infsonewsroom:ContextProjectAcronym/text()',
    ),
    'field_nr_project_coordinator' => array(
      'query' => 'infsonewsroom:ContextProjectCoordinator/text()',
    ),
    'field_newsroom_project' => array(
      'query' => 'infsonewsroom:ContextProjectName',
    ),
    'field_newsroom_project_website:url' => array(
      'query' => 'infsonewsroom:ContextProjectURL',
    ),
    'field_newsroom_project_website:title' => array(
      'query' => 'infsonewsroom:ContextProjectURLDisplay',
    ),
    'field_newsroom_location:wkt' => array(
      'query' => 'infsonewsroom:ContextWellknowntext/text()',
    ),
    'field_highlighted_newsroom_topic' => array(
      'query' => 'category[@infsonewsroom:TopicHighlight="1"]/@infsonewsroom:TopicId',
    ),
    'field_newsroom_ec_content' => array(
      'query' => 'infsonewsroom:ContextECContent',
    ),
    'field_newsroom_item_venue' => array(
      'query' => 'infsonewsroom:ContextVenue/text()',
    ),
    'body' => array(
      'query' => 'infsonewsroom:FullContent',
    ),
    'field_newsroom_item_contact_text' => array(
      'query' => 'infsonewsroom:ContextContactText',
    ),
    'field_newsroom_item_contact_mail' => array(
      'query' => 'infsonewsroom:ContextContactEmail',
    ),
    'field_newsroom_item_linked_obj' => array(
      'query' => 'infsonewsroom:FullLinkedObject',
    ),
    'field_newsroom_item_pre_title' => array(
      'query' => 'infsonewsroom:FullPreTitle',
    ),
    'field_newsroom_item_quote_box' => array(
      'query' => 'infsonewsroom:FullQuoteBox',
    ),
    'field_newsroom_item_short_title' => array(
      'query' => 'infsonewsroom:BasicShortTitle',
    ),
    'field_newsroom_item_speaker' => array(
      'query' => 'infsonewsroom:ContextSpeaker',
    ),
    'field_teaser' => array(
      'query' => 'infsonewsroom:BasicTeaser',
    ),
    '_feed_changed' => array(
      'query' => 'infsonewsroom:pubUpdateDate/text()',
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);

  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, 'newsroom_items_multilingual');

  $importer_values['mapping'][] = array(
    'source' => 'Blank source 1',
    'target' => 'language',
    'unique' => FALSE,
  );

  // Build the importer object.
  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_items_multilingual';
  $feeds_importer->config = array(
    'name' => 'Newsroom Items Multilanguage',
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
        'sources' => $importer_values['queries'],
        'rawXML' => $importer_values['raw_xml'],
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 1,
          'debug' => $importer_values['debug'],
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
        'mappings' => $importer_values['mapping'],
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

  // Create the tamper for the language.
  _nexteuropa_newsroom_dynamic_tamper(NULL);
  // Import the importer.
  _nexteuropa_newsroom_import_importer($feeds_importer);
}

/**
 * Import the multilingual importer.
 */
function _nexteuropa_newsroom_create_multilingual_topics_importer() {
  $def_lang = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'Temporary target 1' => array(
      'query' => '@infsonewsroom:TopicId',
      'target' => 'Temporary target 1',
    ),
    'guid' => array(
      'query' => '@infsonewsroom:TopicId',
      'unique' => 1,
    ),
    'field_newsroom_topic_id' => array(
      'query' => '@infsonewsroom:TopicId',
    ),
    'name' => array(
      'query' => 'text()',
    ),
    'name_field' => array(
      'query' => 'text()',
    ),
    'field_newsroom_category_domain' => array(
      'query' => '@domain',
    ),
    'parentguid' => array(
      'query' => '@infsonewsroom:parentTopicId',
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);

  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, 'newsroom_topics_multilingual');

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_topics_multilingual';
  $feeds_importer->config = array(
    'name' => 'Newsroom Topics Multilingual',
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
        'sources' => $importer_values['queries'],
        'rawXML' => $importer_values['raw_xml'],
        'context' => '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter" and @lang="' . $def_lang . '"]',
        'exp' => array(
          'errors' => 1,
          'debug' => $importer_values['debug'],
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 0,
        'mappings' => $importer_values['mapping'],
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

  // Import the importer.
  _nexteuropa_newsroom_import_importer($feeds_importer);
}

/**
 * Import the multilingual importer.
 */
function _nexteuropa_newsroom_create_multilingual_types_importer() {
  $def_lang = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'guid' => array(
      'query' => 'infsonewsroom:BasicTypeId/text()',
      'unique' => 1,
    ),
    'field_newsroom_type_id' => array(
      'query' => 'infsonewsroom:BasicTypeId/text()',
    ),
    'name' => array(
      'query' => 'title[@lang="' . $def_lang . '"]/text()',
    ),
    'name_field' => array(
      'query' => 'title',
    ),
    'parentguid' => array(
      'query' => '@infsonewsroom:parentTopicId',
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);

  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, 'newsroom_types_multilingual');

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_types_multilingual';
  $feeds_importer->config = array(
    'name' => 'Newsroom Type Multilingual',
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
        'sources' => $importer_values['queries'],
        'rawXML' => $importer_values['raw_xml'],
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => $importer_values['debug'],
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 'newsroom_item_type',
        'mappings' => $importer_values['mapping'],
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

  // Import the importer.
  _nexteuropa_newsroom_import_importer($feeds_importer);
}

/**
 * Import the multilingual importer.
 */
function _nexteuropa_newsroom_create_multilingual_services_importer() {
  $def_lang = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'guid' => array(
      'query' => 'guid/text()',
      'unique' => 1,
    ),
    'field_newsroom_service_id' => array(
      'query' => 'infsonewsroom:BasicSvId/text()',
    ),
    'name' => array(
      'query' => 'title[@lang="' . $def_lang . '"]/text()',
    ),
    'name_field' => array(
      'query' => 'title',
    ),
    'field_newsroom_topic' => array(
      'query' => 'category[@domain="Subchapter"]/@infsonewsroom:TopicId',
    ),
    'field_service_active' => array(
      'query' => 'infsonewsroom:BasicSvStatus/text()',
    ),
    'field_service_type' => array(
      'query' => 'infsonewsroom:BasicSvType',
    ),
    'parentguid' => array(
      'query' => '@infsonewsroom:parentTopicId',
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);

  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, 'newsroom_services_multilingual');

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'newsroom_services_multilingual';
  $feeds_importer->config = array(
    'name' => 'Newsroom Services Multilingual',
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
        'sources' => $importer_values['queries'],
        'rawXML' => $importer_values['raw_xml'],
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 0,
          'debug' => $importer_values['debug'],
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 'newsroom_service',
        'mappings' => $importer_values['mapping'],
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

  // Import the importer.
  _nexteuropa_newsroom_import_importer($feeds_importer);
}
