 <?php
/**
 * @file
 * multisite_newsroom.multilingual.inc
 */

/**
 * Import the multilingual importer.
 */
function _multisite_newsroom_create_multilingual_importer() {
  // Get enabled languages codes.
  $lang_keys = _multisite_newsroom_languages();

  // Define the needed infos to build the importer dinamically.
  $premapping = array(
    'title' => array(
      'query' => 'title[@language="EN"]/text()',
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
    'field_newsroom_item_other_link' => array(
      'query' => 'infsonewsroom:ContextOtherLinkText',
      'language' => TRUE,
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
    ),
    'field_primary_topic' => array(
      'query' => 'category[@infsonewsroom:TopicPrimary="1"]/@infsonewsroom:TopicId',
      'language' => FALSE,
    ),
    'created' => array(
      'query' => 'infsonewsroom:BasicReferenceDate/text()',
      'language' => FALSE,
    ),
    'field_newsroom_category:tid' => array(
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
    'field_highlighted_newsroom_topic' => array(
      'query' => 'category[@infsonewsroom:TopicHighlight="1"]/@infsonewsroom:TopicId',
      'language' => FALSE,
    ),
    'body' => array(
      'query' => 'infsonewsroom:FullContent',
      'language' => TRUE,
    ),
    'language' => array(
      'query' => 'infsonewsroom:NewsLanguage/text()',
      'language' => FALSE,
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

  // Loop through all the fields, build the needed arrays.
  $i = 0;
  foreach ($premapping as $field => $values) {
    // Things look different if the field is translatable.
    if ($values['language']) {
      // If fields are translatable, we create a different mapping for each language.
      foreach ($lang_keys as $lang_key) {
        $upper_key = strtoupper($lang_key);
        // Xpath queries.
        $queries['xpathparser:' . $i] = $values['query'] . '[@language="' . $upper_key . '"]/text()';
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
  // Build also the debug and raw_xml arrays.
  foreach ($queries as $xpath => $query) {
    $debug[$xpath] = $raw_xml[$xpath] = 0;
  }

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
        'sources' => $queries,
        'rawXML' => $raw_xml,
        'context' => '//channel/item',
        'exp' => array(
          'errors' => 1,
          'debug' => $debug,
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
        'mappings' => $mapping,
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

  // Those Api calls are copied from the submit function of the
  // import form provided bt the feeds_ui module. The alpha8 version
  // of Feeds ( the one used in the platform) had a bugged implementation,
  // fixed using the dev version code for the submit.
  $importer = $feeds_importer;
  // Create a copy of the importer to preserve config.
  $save = feeds_importer($importer->id);
  $save->setConfig($importer->config);
  foreach (array('fetcher', 'parser', 'processor') as $type) {
    $save->setPlugin($importer->config[$type]['plugin_key']);
    $save->$type->setConfig($importer->config[$type]['config']);
  }
  $save->save();
}