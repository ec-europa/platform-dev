<?php

/**
 * @file
 * Nexteuropa_newsroom.multilingual.inc.
 */

/**
 * Creates items feed importer and runs the import.
 */
function _nexteuropa_newsroom_create_multilingual_newsletter_importer() {
  $default_language = drupal_strtoupper(language_default()->language);

  $premapping = array(
    'title' => array(
      'query' => 'title[@lang="' . $default_language . '"]/text()',
    ),
    'title_field' => array(
      'query' => 'title',
    ),
    'field_newsroom_nl_issue_date:start' => array(
      'query' => 'pubDate/text()',
      'tamper' => array(
        'plugin_id' => 'strtotime',
      ),
    ),
    'field_newsroom_newsletter_id' => array(
      'query' => 'infsonewsroom:BasicIssueId/text()',
      'unique' => 1,
    ),
    'field_newsroom_item_main_link:url' => array(
      'query' => 'link',
    ),
    'field_newsroom_newsletter_items:etid' => array(
      'query' => 'infsonewsroom:BasicSvItemId/text()',
      'tamper' => array(
        'plugin_id' => 'efq_finder',
        'entity_type' => 'node',
        'bundle' => 'newsroom_item',
        'field' => 'field_newsroom_item_id',
      ),
    ),
    'field_newsroom_service' => array(
      'query' => 'infsonewsroom:BasicSvId/text()',
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => array(
        'entity_type' => 'taxonomy_term',
        'plugin_id' => 'efq_finder',
        'bundle' => NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY,
        'field' => 'field_newsroom_service_id',
      ),
    ),
    'guid' => array(
      'query' => '$field_newsroom_newsletter_id',
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);

  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER);

  $feeds_importer = _nexteuropa_newsroom_build_importer(NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER, 'Newsroom Newsletter issues', 'Imports newsletter issues', $importer_values, NEXTEUROPA_NEWSROOM_NEWSLETTER_CONTENT_TYPE, 'node');

  // Create the tamper for the language.
  _nexteuropa_newsroom_dynamic_tamper(NULL);
  // Import the importer.
  _nexteuropa_newsroom_save_importer($feeds_importer);
}

/**
 * Creates items feed importer and runs the import.
 */
function _nexteuropa_newsroom_create_multilingual_items_importer() {
  $default_language = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'title' => array(
      'query' => 'title[@lang="' . $default_language . '"]/text()',
    ),
    'title_field' => array(
      'query' => 'title',
    ),
    'field_newsroom_item_date:start' => array(
      'query' => 'infsonewsroom:BasicDate/text()',
      'tamper' => array(
        'plugin_id' => 'strtotime',
      ),
    ),
    'field_newsroom_item_date:end' => array(
      'query' => 'infsonewsroom:BasictoDate/text()',
      'tamper' => array(
        'plugin_id' => 'strtotime',
      ),
    ),
    'field_newsroom_private_img:uri' => array(
      'query' => 'enclosure[@type="image/jpeg" and @schema="Private"]/@url',
    ),
    'field_newsroom_illustrative_img:uri' => array(
      'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
    ),
    'field_newsroom_private_img:title' => array(
      'query' => 'infsonewsroom:PicTitle',
      'original_field' => 'field_file_image_title_text',
    ),
    'field_newsroom_private_img:alt' => array(
      'query' => 'infsonewsroom:PicAlt',
      'original_field' => 'field_file_image_alt_text',
    ),
    'field_newsroom_private_img:copyright' => array(
      'query' => 'infsonewsroom:PicCopyright',
      'original_field' => 'field_newsroom_copyrights',
    ),
    'field_newsroom_private_img:caption' => array(
      'query' => 'infsonewsroom:PicCaption',
      'original_field' => 'field_caption',
    ),
    'field_newsroom_illustrative_img:uri' => array(
      'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
    ),
    'field_newsroom_illustrative_img:title' => array(
      'query' => 'infsonewsroom:PicTitle',
      'original_field' => 'field_file_image_title_text',
    ),
    'field_newsroom_illustrative_img:alt' => array(
      'query' => 'infsonewsroom:PicAlt',
      'original_field' => 'field_file_image_alt_text',
    ),
    'field_newsroom_illustrative_img:copyright' => array(
      'query' => 'infsonewsroom:PicCopyright',
      'original_field' => 'field_copyright',
    ),
    'field_newsroom_illustrative_img:caption' => array(
      'query' => 'infsonewsroom:PicCaption',
      'original_field' => 'field_caption',
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
      'tamper' => array(
        'entity_type' => 'taxonomy_term',
        'plugin_id' => 'efq_finder',
        'bundle' => NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY,
        'field' => 'field_newsroom_type_id',
      ),
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
      'unique' => 1,
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
      'query' => 'category[@domain!="Newsletter"]/@infsonewsroom:TopicId',
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => array(
        'plugin_id' => 'efq_finder',
        'entity_type' => 'taxonomy_term',
        'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
        'field' => 'field_newsroom_topic_id',
      ),
    ),
    'field_newsroom_primary_topic' => array(
      'query' => 'category[@infsonewsroom:TopicPrimary="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => array(
        'plugin_id' => 'efq_finder',
        'entity_type' => 'taxonomy_term',
        'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
        'field' => 'field_newsroom_topic_id',
      ),
    ),
    'created' => array(
      'query' => 'infsonewsroom:BasicReferenceDate/text()',
      'tamper' => array(
        'plugin_id' => 'strtotime',
      ),
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
    'field_newsroom_related_content' => array(
      'query' => 'infsonewsroom:slave/@id',
    ),
    'field_newsroom_parent_content' => array(
      'query' => 'infsonewsroom:master/@id',
    ),
    'field_newsroom_project_acr' => array(
      'query' => 'infsonewsroom:ContextProjectAcronym/text()',
    ),
    'field_newsroom_prj_coordinator' => array(
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
    'field_newsroom_highlighted_topic' => array(
      'query' => 'category[@infsonewsroom:TopicHighlight="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
      'options' => array(
        'term_search' => '1',
        'autocreate' => 0,
      ),
      'tamper' => array(
        'plugin_id' => 'efq_finder',
        'entity_type' => 'taxonomy_term',
        'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
        'field' => 'field_newsroom_topic_id',
      ),
    ),
    'field_newsroom_ec_content' => array(
      'query' => 'infsonewsroom:ContextECContent/text()',
    ),
    'field_newsroom_item_venue' => array(
      'query' => 'infsonewsroom:ContextVenue',
    ),
    'field_newsroom_organiser' => array(
      'query' => 'infsonewsroom:ContextOrganiser',
    ),
    'field_newsroom_author' => array(
      'query' => 'infsonewsroom:ContextAuthor',
    ),
    'field_newsroom_eur_lex_link:url' => array(
      'query' => 'infsonewsroom:ContextEurlex',
    ),
    'field_newsroom_ted_link:url' => array(
      'query' => 'infsonewsroom:ContextTed',
    ),
    'field_newsroom_registration_link:url' => array(
      'query' => 'infsonewsroom:ContextRegistrationLink',
    ),
    'field_newsroom_registration_link:title' => array(
      'query' => 'infsonewsroom:ContextRegistrationLinkText',
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
    'field_newsroom_teaser' => array(
      'query' => 'infsonewsroom:BasicTeaser',
    ),
    'guid' => array(
      'query' => '$field_newsroom_item_id',
    ),
    '_feed_changed' => array(
      'query' => 'infsonewsroom:pubUpdateDate/text()',
      'tamper' => array(
        'plugin_id' => 'strtotime',
      ),
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);

  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, NEXTEUROPA_NEWSROOM_ITEM_IMPORTER);

  $importer_values['mapping'][] = array(
    'source' => 'Blank source 1',
    'target' => 'language',
    'unique' => FALSE,
  );

  $feeds_importer = _nexteuropa_newsroom_build_importer(NEXTEUROPA_NEWSROOM_ITEM_IMPORTER, 'Newsroom Items Multilanguage', 'Imports Newsroom Items from the Newsroom service', $importer_values, NEXTEUROPA_NEWSROOM_CONTENT_TYPE, 'node');

  // Create the tamper for the language.
  _nexteuropa_newsroom_dynamic_tamper(NULL);
  // Import the importer.
  _nexteuropa_newsroom_save_importer($feeds_importer);
}

/**
 * Builds importer class.
 *
 * @param string $id
 *   Importer ID.
 * @param string $title
 *   Importer title.
 * @param string $description
 *   Importer description.
 * @param array $importer_values
 *   Importer info.
 * @param string $bundle
 *   Importer bundle.
 * @param string $type
 *   Entity type.
 * @param string $rss_context
 *   Xpath context.
 * @param int $import_period
 *   Period in seconds.
 *
 * @return \stdClass
 *   Importer class.
 */
function _nexteuropa_newsroom_build_importer($id, $title, $description, $importer_values, $bundle, $type = 'node', $rss_context = '//channel/item', $import_period = 3600) {
  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = $id;
  $feeds_importer->config = array(
    'name' => $title,
    'description' => $description,
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
        'context' => $rss_context,
        'exp' => array(
          'errors' => 0,
          'debug' => $importer_values['debug'],
        ),
        'allow_override' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => $import_period,
    'expire_period' => 1800,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );

  if ($type == 'node') {
    $feeds_importer->config['processor'] = array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '0',
        'authorize' => 0,
        'mappings' => $importer_values['mapping'],
        'update_existing' => '2',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => $bundle,
      ),
    );
  }
  else {
    $feeds_importer->config['processor'] = array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => $bundle,
        'mappings' => $importer_values['mapping'],
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => $bundle,
      ),
    );
  }

  return $feeds_importer;
}

/**
 * Creates topics feed importer and runs the import.
 */
function _nexteuropa_newsroom_create_multilingual_topics_importer() {
  $default_language = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'Temporary target 1' => array(
      'query' => '@infsonewsroom:TopicId',
      'target' => 'Temporary target 1',
    ),
    'guid' => array(
      'query' => '@nrid',
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
      'tamper' => array(
        'plugin_id' => 'rewrite',
        'prefix' => 'topic-',
      ),
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);
  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER);
  $rss_context = '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter" and @lang="' . $default_language . '"]';
  $feeds_importer = _nexteuropa_newsroom_build_importer(NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER, 'Newsroom Topics Multilingual', 'Imports Topics from the Newsroom service', $importer_values, NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY, 'taxonomy_term', $rss_context, -1);

  // Import the importer.
  _nexteuropa_newsroom_save_importer($feeds_importer);
}

/**
 * Creates types feed importer and runs the import.
 */
function _nexteuropa_newsroom_create_multilingual_types_importer() {
  $default_language = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'guid' => array(
      'query' => '@nrid',
      'unique' => 1,
    ),
    'field_newsroom_type_id' => array(
      'query' => 'infsonewsroom:BasicTypeId/text()',
    ),
    'name' => array(
      'query' => 'title[@lang="' . $default_language . '"]/text()',
    ),
    'name_field' => array(
      'query' => 'title',
    ),
    'parentguid' => array(
      'query' => 'infsonewsroom:BasicTypeParent/text()',
      'tamper' => array(
        'plugin_id' => 'rewrite',
        'prefix' => 'type-',
      ),
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);
  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, NEXTEUROPA_NEWSROOM_TYPE_IMPORTER);
  $feeds_importer = _nexteuropa_newsroom_build_importer(NEXTEUROPA_NEWSROOM_TYPE_IMPORTER, 'Newsroom Type Multilingual', 'Imports Item Types from the Newsroom service.', $importer_values, NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY, 'taxonomy_term', '//channel/item', -1);

  // Import the importer.
  _nexteuropa_newsroom_save_importer($feeds_importer);
}

/**
 * Creates services feed importer and runs the import.
 */
function _nexteuropa_newsroom_create_multilingual_services_importer() {
  $default_language = drupal_strtoupper(language_default()->language);
  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'guid' => array(
      'query' => '@nrid',
      'unique' => 1,
    ),
    'field_newsroom_service_id' => array(
      'query' => 'infsonewsroom:BasicSvId/text()',
    ),
    'name' => array(
      'query' => 'title[@lang="' . $default_language . '"]/text()',
    ),
    'name_field' => array(
      'query' => 'title',
    ),
    'field_newsroom_topic' => array(
      'query' => 'category[@domain="Subchapter"]/@infsonewsroom:TopicId',
    ),
    'field_newsroom_service_active' => array(
      'query' => 'infsonewsroom:BasicSvStatus/text()',
    ),
    'field_newsroom_service_type' => array(
      'query' => 'infsonewsroom:BasicSvType',
    ),
    'description' => array(
      'query' => 'description/text()',
    ),
    'field_newsroom_basic_mailing' => array(
      'query' => 'infsonewsroom:BasicSvMailing/text()',
    ),
    'field_newsroom_service_image:uri' => array(
      'query' => 'infsonewsroom:BasicSvVisuUrl/text()',
    ),
    'parentguid' => array(
      'query' => '@infsonewsroom:parentTopicId',
      'tamper' => array(
        'plugin_id' => 'rewrite',
        'prefix' => 'service-',
      ),
    ),
  );

  $premapping = _nexteuropa_newsroom_check_translations($premapping);
  $importer_values = _nexteuropa_newsroom_prepare_dynamic_mapping($premapping, NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER);
  $feeds_importer = _nexteuropa_newsroom_build_importer(NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER, 'Newsroom Services Multilingual', 'Imports Services from the Newsroom service.', $importer_values, NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY, 'taxonomy_term', '//channel/item', -1);

  // Import the importer.
  _nexteuropa_newsroom_save_importer($feeds_importer);
}

/**
 * Enables languages.
 *
 * @param array $premapping
 *   The values to elaborate.
 * @param string $type
 *   Taxonomy or node.
 *
 * @return array
 *   Array containing the needed info for the importer.
 */
function _nexteuropa_newsroom_prepare_dynamic_mapping(array $premapping, $type = NULL) {
  $default_language = drupal_strtoupper(language_default()->language);
  // Get enabled languages codes.
  $lang_keys = NewsroomHelper::getEnabledLanguages();
  // Loop through all the fields, build the needed arrays.
  $i = 0;
  $queries = array();
  $mapping = array();

  foreach ($premapping as $field => $values) {
    if (isset($values['tamper'])) {
      $tamper = _nexteuropa_newsroom_prepare_dynamic_tamper($values['tamper'], $i, $type);
      _nexteuropa_newsroom_dynamic_tamper($tamper);
    }

    // Things look different if the field is translatable.
    if ($values['language']) {
      // If fields are translatable,
      // we create a different mapping for each language.
      foreach ($lang_keys as $lang_key) {
        $upper_key = drupal_strtoupper($lang_key);
        // Xpath queries.
        $queries['xpathparser:' . $i] = $values['query'] . '[@lang="' . $upper_key . '"]/text()';

        if (strpos($type, 'topic') && $upper_key != $default_language) {
          $queries['xpathparser:' . $i] = '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter" and @lang="' . $upper_key . '" and @infsonewsroom:TopicId="$Temporary target 1"]/' . $values['query'];
        }
        elseif (strpos($type, 'topic') && $upper_key == $default_language) {
          $queries['xpathparser:' . $i] = $values['query'];
        }
        elseif (strpos($type, 'newsroom_types')) {
          $queries['xpathparser:' . $i] = $values['query'] . '[@lang="' . $upper_key . '"]/text()';
        }
        // Mapping arrays.
        $mapping[$i] = array(
          'source' => 'xpathparser:' . $i,
          'target' => $field . ':et:' . $lang_key,
          'unique' => FALSE,
        );
        // Additional values.
        if (isset($values['options'])) {
          foreach ($values['options'] as $key => $option) {
            $mapping[$i][$key] = $option;
          }
        }
        // Guid is the "unique" field but let's do this "dinamically".
        if (isset($values['unique'])) {
          $mapping[$i]['unique'] = TRUE;
        }
        $i++;
      }
    }
    // Not translatable fields.
    else {
      // Xpath queries.
      $queries['xpathparser:' . $i] = $values['query'];
      // Mapping arrays.
      $mapping[$i] = array(
        'source' => 'xpathparser:' . $i,
        'target' => $field,
        'unique' => FALSE,
      );

      if (isset($values['options'])) {
        foreach ($values['options'] as $key => $option) {
          $mapping[$i][$key] = $option;
        }
      }
      if (isset($values['unique'])) {
        $mapping[$i]['unique'] = TRUE;
      }
      $i++;
    }
  }

  $debug = array();
  $raw_xml = array();
  // Build also the debug and raw_xml arrays.
  foreach ($queries as $xpath => $query) {
    $debug[$xpath] = $raw_xml[$xpath] = 0;
  }

  return array(
    'mapping' => $mapping,
    'queries' => $queries,
    'debug' => $debug,
    'raw_xml' => $raw_xml,
  );
}

/**
 * Enables languages.
 *
 * @param object $importer
 *   The importer to import.
 */
function _nexteuropa_newsroom_save_importer($importer) {
  $save = feeds_importer($importer->id);
  $save->setConfig($importer->config);

  foreach (array('fetcher', 'parser', 'processor') as $type) {
    $save->setPlugin($importer->config[$type]['plugin_key']);
    $save->$type->setConfig($importer->config[$type]['config']);
  }

  $save->save();

  // Set default URLS for importers.
  $source = feeds_source($importer->id);
  $config = $source->getConfig();
  $config['FeedsHTTPFetcher']['source'] = NewsroomHelper::getImporterUrl($importer->id);
  $source->setConfig($config);
  $source->save();
}

/**
 * Prepares the tamper settings.
 *
 * @param string $settings
 *   Tamper settings.
 * @param int $i
 *   The order in the parser.
 * @param string $type
 *   Taxonomy or node.
 *
 * @return array
 *   Tamper settings.
 */
function _nexteuropa_newsroom_prepare_dynamic_tamper($settings, $i, $type = NULL) {
  $str = 'xpathparser_' . $i;
  $tamper = array(
    'id' => $type . '-' . $str . '-' . $settings['plugin_id'],
    'importer' => $type,
    'source' => 'xpathparser:' . $i,
    'plugin_id' => $settings['plugin_id'],
  );

  // Prepare setting for Entity Field Query finder.
  if ($settings['plugin_id'] == 'efq_finder') {
    $tamper += array(
      'settings' => array(
        'entity_type' => $settings['entity_type'],
        'bundle' => $settings['bundle'],
        'column' => 'value',
        'property' => FALSE,
        'update' => 'Update',
        'field' => $settings['field'],
      ),
      'description' => 'Entity Field Query finder',
    );
  }

  // Prepare setting for Rewrite plugin.
  if ($settings['plugin_id'] == 'rewrite') {
    $tamper += array(
      'settings' => array(
        'text' => $settings['prefix'] . '[xpathparser:' . $i . ']',
      ),
      'description' => 'Rewrite',
    );
  }

  // String to timestamp plugin.
  if ($settings['plugin_id'] == 'strtotime') {
    $tamper += array(
      'settings' => '',
      'description' => 'String to Unix timestamp',
    );
  }

  return $tamper;
}

/**
 * Builds tampers programmatically.
 *
 * @param array $tamper
 *   Tamper array.
 */
function _nexteuropa_newsroom_dynamic_tamper($tamper) {
  $default_language = language_default()->language;
  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE;
  $feeds_tamper->api_version = 2;
  $feeds_tamper->export_type = 0;
  $feeds_tamper->weight = 0;
  if ($tamper == NULL) {
    $feeds_tamper->id = 'newsroom_items_multilingual-blank_source_1-default_value';
    $feeds_tamper->importer = NEXTEUROPA_NEWSROOM_ITEM_IMPORTER;
    $feeds_tamper->source = 'Blank source 1';
    $feeds_tamper->plugin_id = 'default_value';
    $feeds_tamper->settings = array(
      'default_value' => $default_language,
    );
    $feeds_tamper->description = 'Set default language';
  }
  else {
    $feeds_tamper->id = $tamper['id'];
    $feeds_tamper->importer = $tamper['importer'];
    $feeds_tamper->source = $tamper['source'];
    $feeds_tamper->plugin_id = $tamper['plugin_id'];
    $feeds_tamper->settings = $tamper['settings'];
    $feeds_tamper->description = $tamper['description'];
  }

  // Delete a pre-existing tamper with the same id.
  db_delete('feeds_tamper')
    ->condition('id', $feeds_tamper->id)
    ->execute();
  // Save the tamper.
  feeds_tamper_save_instance($feeds_tamper);
}

/**
 * Checks if a field is translatable.
 *
 * @param array $premapping
 *   Premappings array.
 *
 * @return array
 *   Prepared premappings array.
 */
function _nexteuropa_newsroom_check_translations(array $premapping) {
  $fields = field_info_fields();
  // Build an array with langauge settings for the fields.
  foreach ($premapping as $fieldname => $values) {
    // Sanitize fieldname.
    $attribute = strrchr($fieldname, ':');
    $sanitized_name = isset($values['original_field']) ? $values['original_field'] : str_replace($attribute, '', $fieldname);
    $field = field_info_field($sanitized_name);
    $language = field_is_translatable('node', $field);
    $premapping[$fieldname]['language'] = $language;
    if (isset($fields[$sanitized_name])) {
      $language = field_is_translatable('node', $fields[$sanitized_name]);
      $premapping[$fieldname]['language'] = $language;
    }
  }

  return $premapping;
}
