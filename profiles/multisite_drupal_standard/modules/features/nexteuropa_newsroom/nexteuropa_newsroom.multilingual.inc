 <?php
/**
 * @file
 * nexteuropa_newsroom.multilingual.inc
 */


/**
 * Import the multilingual importer.
 */
function _nexteuropa_newsroom_create_multilingual_items_importer() {
  $def_lang = strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'title' => array(
      'query' => 'title[@lang="EN"]/text()',
      'language' => FALSE,
    ),
    'title_field' => array(
      'query' => 'title',
      'language' => TRUE,
    ),
    'guid' => array(
      'query' => 'guid/text()',
      'language' => FALSE,
      'unique' => 1,
    ),
    'field_newsroom_item_date:start' => array(
      'query' => 'infsonewsroom:BasicDate/text()',
      'language' => FALSE,
    ),
    'field_newsroom_item_date:end' => array(
      'query' => 'infsonewsroom:BasictoDate/text()',
      'language' => FALSE,
    ),
    'field_illustrative_image' => array(
      'query' => 'enclosure[@type="image/jpeg"]/@url',
      'language' => FALSE,
    ),
    'field_illustrative_image:alt' => array(
      'query' => 'enclosure[@type="image/jpeg"]/@alt',
      'language' => FALSE,
    ),
    'field_illustrative_image:text' => array(
      'query' => 'enclosure[@type="image/jpeg"]/@title',
      'language' => FALSE,
    ), 
    'field_illustrative_image:copyright' => array(
      'query' => 'enclosure[@type="image/jpeg"]/@copyright',
      'language' => FALSE,
    ), 
    'field_newsroom_item_rapid_pr' => array(
      'query' => 'infsonewsroom:BasicRapidPressRelease/text()',
      'language' => FALSE,
    ),
    'field_newsroom_item_type' => array(
      'query' => 'infsonewsroom:NewsType/@id',
      'language' => FALSE,
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => TRUE,
      'vocabulary' => 'newsroom_item_type',
      'field' => 'field_newsroom_type_id'
    ),
    'field_tags' => array(
      'query' => 'category[@domain="Policy" or @domain="Activity" or @domain="Theme" or @domain="Collection" or @domain="Tag"]/text()',
      'language' => FALSE,
      'options' => array(
        'term_search' => '0',
        'autocreate' => 0,
      ),
    ),
    'field_newsroom_item_id' => array(
      'query' => 'infsonewsroom:BasicId',
      'language' => FALSE,
    ),
    'field_newsroom_item_other_link:title' => array(
      'query' => 'infsonewsroom:ContextOtherLinkText',
      'language' => TRUE,
    ),
    'field_newsroom_item_other_link:url' => array(
      'query' => 'infsonewsroom:ContextOtherLinkUrl',
      'language' => TRUE,
    ),
    'field_newsroom_documents:url' => array(
      'query' => 'enclosure[not(@type="image/jpeg")]/@url',
      'language' => FALSE,
    ),
    'field_newsroom_documents:title' => array(
      'query' => 'enclosure[not(@type="image/jpeg")]/@title',
      'language' => FALSE,
    ),
    'promote' => array(
      'query' => 'infsonewsroom:pubHighlight/text()',
      'language' => FALSE,
    ),
    'field_newsroom_topics' => array(
      'query' => 'category/@infsonewsroom:TopicId',
      'language' => FALSE,
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
      'language' => FALSE,
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
      'language' => FALSE,
    ),
    'field_newsroom_category:etid' => array(
      'query' => 'category[@domain="Collection"]/@infsonewsroom:TopicId',
      'language' => FALSE,
    ),
    'sticky' => array(
      'query' => 'infsonewsroom:pubIsCentral/text()',
      'language' => FALSE,
    ),
    'field_newsroom_short_item' => array(
      'query' => 'infsonewsroom:pubIsLong/text()',
      'language' => FALSE,
    ),
    'field_newsroom_teaser_only' => array(
      'query' => 'infsonewsroom:pubTeaserOnly/text()',
      'language' => FALSE,
    ),
    'field_related_content' => array(
      'query' => 'infsonewsroom:slave/@guid',
      'language' => FALSE,
    ),
    'field_newsroom_project_acr' => array(
      'query' => 'infsonewsroom:ContextProjectAcronym/text()',
      'language' => FALSE,
    ),
    'field_nr_project_coordinator' => array(
      'query' => 'infsonewsroom:ContextProjectCoordinator/text()',
      'language' => FALSE,
    ),
    'field_newsroom_project' => array(
      'query' => 'infsonewsroom:ContextProjectName',
      'language' => TRUE,
    ),
    'field_newsroom_project_website:url' => array(
      'query' => 'infsonewsroom:ContextProjectURL/text()',
      'language' => FALSE,
    ),
    'field_newsroom_project_website:title' => array(
      'query' => 'infsonewsroom:ContextProjectURLDisplay/text()',
      'language' => FALSE,
    ),  
    'field_newsroom_location:wkt' => array(
      'query' => 'infsonewsroom:ContextWellknowntext/text()',
      'language' => FALSE,
    ),
    'field_highlighted_newsroom_topic' => array(
      'query' => 'category[@infsonewsroom:TopicHighlight="1"]/@infsonewsroom:TopicId',
      'language' => FALSE,
    ),
    'field_newsroom_ec_content' => array(
      'query' => 'infsonewsroom:ContextECContent',
      'language' => FALSE,
    ),
    'field_newsroom_item_venue' => array(
      'query' => 'infsonewsroom:ContextVenue/text()',
      'language' => FALSE,
    ),
    'body' => array(
      'query' => 'infsonewsroom:FullContent',
      'language' => TRUE,
    ),
    'field_newsroom_item_contact_text' => array(
      'query' => 'infsonewsroom:ContextContactText',
      'language' => TRUE,
    ),
    'field_newsroom_item_contact_mail' => array(
      'query' => 'infsonewsroom:ContextContactEmail',
      'language' => TRUE,
    ),
    'field_newsroom_item_linked_obj' => array(
      'query' => 'infsonewsroom:FullLinkedObject',
      'language' => TRUE,
    ),
    'field_newsroom_item_pre_title' => array(
      'query' => 'infsonewsroom:FullPreTitle',
      'language' => TRUE,
    ),
    'field_newsroom_item_quote_box' => array(
      'query' => 'infsonewsroom:FullQuoteBox',
      'language' => TRUE,
    ),
    'field_newsroom_item_short_title' => array(
      'query' => 'infsonewsroom:BasicShortTitle',
      'language' => TRUE,
    ),
    'field_newsroom_item_speaker' => array(
      'query' => 'infsonewsroom:ContextSpeaker',
      'language' => TRUE,
    ),
    'field_teaser' => array(
      'query' => 'infsonewsroom:BasicTeaser',
      'language' => TRUE,
    ),
  );

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

 // Import the importer.
  _nexteuropa_newsroom_import_importer($feeds_importer);
}
//translation[@English='title']/@*[local-name()=//agentlang]" />
/**
 * Import the multilingual importer.
 */
function _nexteuropa_newsroom_create_multilingual_topics_importer() {
  $def_lang = strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'Temporary target 1' => array(
      'query' => '@infsonewsroom:TopicId',
      'target' => 'Temporary target 1',
      'language' => FALSE,
    ),
    'guid' => array(
      'query' => '@infsonewsroom:TopicId',
      'language' => FALSE,
      'unique' => 1,
    ),
    'field_newsroom_topic_id' => array(
      'query' => '@infsonewsroom:TopicId',
      'language' => FALSE,
    ), 
    'name' => array(
      'query' => 'text()',
      'language' => FALSE,
    ), 
    'name_field' => array(
      'query' => 'text()',
      'language' => TRUE,
    ),  
    'field_newsroom_category_domain' => array(
      'query' => '@domain',
      'language' => TRUE,
    ),  
    'parentguid' => array(
      'query' => '@infsonewsroom:parentTopicId',
      'language' => FALSE,
    ), 
  );

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
  $def_lang = strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'guid' => array(
      'query' => 'infsonewsroom:BasicTypeId/text()',
      'language' => FALSE,
      'unique' => 1,
    ),
    'field_newsroom_type_id' => array(
      'query' => 'infsonewsroom:BasicTypeId/text()',
      'language' => FALSE,
    ), 
    'name' => array(
      'query' => 'title[@lang="' . $def_lang . '"]/text()',
      'language' => FALSE,
    ), 
    'name_field' => array(
      'query' => 'title',
      'language' => TRUE,
    ),   
    'parentguid' => array(
      'query' => '@infsonewsroom:parentTopicId',
      'language' => FALSE,
    ), 
  );

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
  $def_lang = strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'guid' => array(
      'query' => 'guid/text()',
      'language' => FALSE,
      'unique' => 1,
    ),
    'field_newsroom_service_id' => array(
      'query' => 'infsonewsroom:BasicSvId/text()',
      'language' => FALSE,
    ), 
    'name' => array(
      'query' => 'title[@lang="' . $def_lang . '"]/text()',
      'language' => FALSE,
    ), 
    'name_field' => array(
      'query' => 'title',
      'language' => TRUE,
    ),
    'field_newsroom_topic' => array(
      'query' => 'category[@domain="Subchapter"]/@infsonewsroom:TopicId',
      'language' => FALSE,
    ),  
    'field_service_active' => array(
      'query' => 'infsonewsroom:BasicSvStatus/text()',
      'language' => FALSE,
    ),  
    'field_service_type' => array(
      'query' => 'infsonewsroom:BasicSvType',
      'language' => TRUE,
    ),  
    'parentguid' => array(
      'query' => '@infsonewsroom:parentTopicId',
      'language' => FALSE,
    ), 
  );

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