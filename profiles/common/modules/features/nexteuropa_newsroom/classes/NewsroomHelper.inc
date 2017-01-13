<?php

/**
 * @file
 * Code for the NewsroomHelper class.
 */

/**
 * NewsroomHelper class.
 */
class NewsroomHelper {

  /**
   * Merges a term_tid and it's children into one array.
   *
   * @param int $term_tid
   *   Term id.
   *
   * @return array.
   *   tids
   */
  public static function getTypeChildren($term_tid) {
    $types = NewsroomHelper::getNewsroomTypes();
    $children_items = NewsroomHelper::findChildrenById($types, $term_tid);
    // We need parent ID also in the output array to use it in query.
    $parent_children_tids = array($term_tid);
    $children_tids = array_keys($children_items);
    if (count($children_tids) > 0) {
      $parent_children_tids = array_merge($parent_children_tids, $children_tids);
    }

    return $parent_children_tids;
  }

  /**
   * Generates newsroom page URL.
   *
   * @param array $url_parts
   *   Url parts.
   *
   * @return string
   *   Newsroom page URL.
   */
  public static function getNewsroomPageUrl($url_parts = array()) {
    return 'newsroom/' . implode('/', $url_parts);
  }

  /**
   * Generates newsroom rss URL.
   *
   * @param array $url_parts
   *   Url parts.
   *
   * @return string
   *   Newsroom rss URL.
   */
  public static function getNewsroomRssUrl($url_parts = array()) {
    return 'newsroom-rss/' . implode('/', $url_parts);
  }

  /**
   * Prepares options for the content type select.
   *
   * @param string $type
   *   Type of the options to generate.
   *
   * @return array
   *   Array of options.
   */
  public static function prepareOptions($type) {
    $options = array();
    if (is_numeric($type)) {
      for ($i = 1; $i <= $type; $i++) {
        $options[$i] = $i;
      }
    }
    else {
      // Get a list of the existing content type.
      $content_types = node_type_get_types();
      // Exclude the ct used for the import.
      unset($content_types[NEXTEUROPA_NEWSROOM_CONTENT_TYPE]);
      unset($content_types['newsroom_selection']);
      // Build options for selecting content types.
      foreach ($content_types as $name => $content_type) {
        if ($content_type->disabled !== 1) {
          $options[$name] = $content_type->name;
        }
      }
    }
    return $options;
  }

  /**
   * Calls feed importer with the certain URL.
   *
   * @param string $importer_id
   *   Importer ID.
   * @param string $url
   *   RSS feed URL to call.
   */
  public static function runFeedImporter($importer_id, $url = NULL) {
    $source = feeds_source($importer_id);
    $config = $source->getConfig();

    if (!empty($url)) {
      $config['FeedsHTTPFetcher']['source'] = $url;
      $source->setConfig($config);
    }

    $source->import();

    if (!empty($url)) {
      // Restore the default URL in order to run importers manually or via cron.
      $config['FeedsHTTPFetcher']['source'] = NewsroomHelper::getImporterUrl($importer_id);
      $source->setConfig($config);
      $source->save();
    }
  }

  /**
   * Gets default URL of importer.
   *
   * @param string $importer_id
   *   Importer ID.
   *
   * @return string
   *   URL.
   */
  public static function getImporterUrl($importer_id) {
    $url = '';

    switch ($importer_id) {

      case NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER:
      case NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER:
        $url = NewsroomHelper::getNewsroomUrl(NEXTEUROPA_NEWSROOM_TOPIC_SCRIPT);
        break;

      case NEXTEUROPA_NEWSROOM_TYPE_IMPORTER:
        $url = NewsroomHelper::getNewsroomUrl(NEXTEUROPA_NEWSROOM_TYPE_SCRIPT);
        break;

      case NEXTEUROPA_NEWSROOM_ITEM_IMPORTER:
        $subsite = variable_get('newsroom_subsite', FALSE);
        $subsite_url_part = '';

        if ($subsite) {
          $subsite_url_part = '?subsite=' . $subsite;
        }

        $url = NewsroomHelper::getNewsroomUrl(NEXTEUROPA_NEWSROOM_ITEM_SCRIPT) . $subsite_url_part;
        break;

      case NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER:
        $url = NewsroomHelper::getNewsroomUrl(NEXTEUROPA_NEWSROOM_NEWSLETTER_SCRIPT);
        break;
    }

    return $url;
  }

  /**
   * Gets newsroom item by original newsroom Id.
   *
   * @param string $field_name
   *   Field name.
   * @param int $newsroom_id
   *   Newsroom original ID.
   *
   * @return object
   *   Newsroom item.
   */
  public static function getNodeByFieldValue($field_name, $newsroom_id = 0) {
    $newsroom_data = &drupal_static(__FUNCTION__);
    $cache_key = 'newsroom_item_by_id:' . $newsroom_id;
    if (!isset($newsroom_data)) {
      if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
        $newsroom_data = $cache->data;
      }
      else {
        $query = new EntityFieldQuery();
        $newsroom_item = $query
          ->entityCondition('entity_type', 'node')
          ->fieldCondition($field_name, 'value', $newsroom_id, '=')
          ->execute();
        $newsroom_data = isset($newsroom_item['node']) ? array_shift($newsroom_item['node']) : FALSE;
        cache_set($cache_key, $newsroom_data, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
      }
    }
    return $newsroom_data;
  }

  /**
   * Finds a menu item for a given path.
   *
   * @param string $path
   *   Drupal intermal url.
   *
   * @return array
   *   Menu item.
   */
  public static function getMenuByPath($path) {
    $cache_key = 'get_menu_by_path' . md5($path);
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $query = db_select('menu_links', 'ml')
        ->fields('ml')
        ->condition('ml.link_path', $path)
        ->execute();
      $data = $query->fetchAll();
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_get_menu_by_path', 86400));
    }
    return $data;
  }

  /**
   * Retrieves nodes associated with topics.
   *
   * @param string $topic_ids
   *   Topic term ids.
   *
   * @return array
   *   Field data.
   */
  public static function getNodesAssociatedToTopics($topic_ids) {
    $topic_ids = is_array($topic_ids) ? $topic_ids : array($topic_ids);
    $cache_key = 'get_topic_entities' . md5(implode('', $topic_ids));
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $query = db_select('field_data_field_newsroom_associated_topic', 'f')
        ->fields('f')
        ->condition('f.field_newsroom_associated_topic_tid', $topic_ids)
        ->execute();
      $data = $query->fetchAll();

      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_get_topic_entities', 3600));
    }
    return $data;
  }

  /**
   * Returns active menu item for a newsroom item.
   *
   * @param int $topic_id
   *   Topic ID.
   *
   * @return string
   *   Menu path.
   */
  public static function fetchActiveMenuPath($topic_id) {
    $cache_key = 'fetch_active_menu' . $topic_id;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $path = $cache->data;
    }
    else {
      $path = FALSE;
      // Check if they are added to menu.
      $menu_items = array();
      // Fetch entities associated to topic using the special field.
      $topic_entities = NewsroomHelper::getNodesAssociatedToTopics($topic_id);
      if (count($topic_entities) > 0) {
        foreach ($topic_entities as $entity) {
          // Could use entity_uri() but we would have to load the full entity.
          $menu_link_items = NewsroomHelper::getMenuByPath(str_replace('_', '/', $entity->entity_type) . '/' . $entity->entity_id);
          if (!empty($menu_link_items)) {
            foreach ($menu_link_items as $menu_item) {
              $menu_items[] = $menu_item;
            }
          }
        }
      }

      if (count($menu_items) > 0) {
        // Favor terms over nodes and lower entity ID in case we have multiple.
        usort($menu_items, function ($a, $b) {
          if ($a->router_path == 'taxonomy/term/%' && $b->router_path == 'node/%') {
            return -1;
          }
          elseif ($a->router_path == 'node/%' && $b->router_path == 'taxonomy/term/%') {
            return 1;
          }
          else {
            $fields = array(
              'p1', 'p2', 'p3',
              'p4', 'p5', 'p6',
              'p7', 'p8', 'p9',
              'plid', 'weight', 'mlid',
            );
            $result = 0;
            foreach ($fields as $field) {
              if ($a->{$field} == $b->{$field}) {
                continue;
              }
              else {
                $result = $a->{$field} < $b->{$field} ? -1 : 1;
              }
            }
            return $result;
          }
        });
        $menu_item_link = array_shift($menu_items);
        $path = $menu_item_link->link_path;
      }
      cache_set($cache_key, $path, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_fetch_active_menu', 3600));
    }

    return $path;
  }

  /**
   * Tries to resolve each taxonomy term with a corresponding ID to map.
   *
   * @param string $field_name
   *   The mapping field.
   * @param string $field_value
   *   The mapping field value.
   *
   * @return array
   *   Taxonomy ids.
   */
  public static function getTaxonomyTermFromField($field_name, $field_value, $bundle = NULL) {
    $field_value = is_array($field_value) ? $field_value : array($field_value);
    $cache_key = 'tech_field_tid:' . md5($field_name . implode('', $field_value) . $bundle);

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $term_ids = $cache->data;
    }
    else {
      $term_ids = array();
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'taxonomy_term')
        ->fieldCondition($field_name, 'value', $field_value);
      if ($bundle) {
        $query->entityCondition('bundle', $bundle);
      }
      $result = $query->execute();
      if (isset($result['taxonomy_term'])) {
        $term_ids = array_keys($result['taxonomy_term']);
      }

      cache_set($cache_key, $term_ids, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    }
    return $term_ids;
  }

  /**
   * Gets events Terms ids.
   *
   * @return array
   *   Newsroom type taxonomy terms array.
   */
  public static function getEventsTermsIds() {
    $event_type_ids = array();
    $types = NewsroomHelper::getNewsroomTypes();
    $behavior_types = array(
      'consultation_funding',
      'events',
      'agenda',
      'call',
    );
    foreach ($types as $type) {
      if (in_array(NewsroomHelper::getFieldValue($type, 'field_newsroom_type'), $behavior_types)) {
        $event_type_ids[] = $type->tid;
      }
    }

    return $event_type_ids;
  }

  /**
   * Returns universe URL.
   *
   * @return string
   *   Universe URL.
   */
  public static function getUniverseUrl() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $data = variable_get('newsroom_base_url', NEXTEUROPA_NEWSROOM_BASE_URL) . NewsroomHelper::getUniverseId() . '/';
    }
    return $data;
  }

  /**
   * Gets the existing instances of fields.
   *
   * @param string $type
   *   Select or topic for the moment.
   *
   * @return array
   *   instances
   */
  public static function getFieldInstances($type) {
    // Get instances per field.
    $instances = array();
    if ($type) {
      $field_name = 'field_newsroom_associated_' . $type;
      $mappings = field_info_field_map();
      if (isset($mappings[$field_name]['bundles']['node'])) {
        $instances = $mappings[$field_name]['bundles']['node'];
      }
    }
    return $instances;
  }

  /**
   * Tries to get taxonomy URL part (taxonomy term name).
   *
   * @param string $request_name
   *   URL request part.
   * @param string $vocabulary_name
   *   Vocabulary name.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getTermFromRequest($request_name, $vocabulary_name) {
    $cache_key = 'newsroom:term_from_request:' . md5($request_name . $vocabulary_name);

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $taxonomy_term = $cache->data;
    }
    else {
      $taxonomy_term = NULL;
      if (is_int($request_name)) {
        $taxonomy_term = taxonomy_term_load($request_name);
      }

      if (!$taxonomy_term) {
        $taxonomy_terms = array();

        if ($vocabulary_name == NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY) {
          $taxonomy_terms = array_merge($taxonomy_terms, NewsroomHelper::getNewsroomTypes());
        }
        elseif ($vocabulary_name == NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY) {
          $taxonomy_terms = array_merge($taxonomy_terms, NewsroomHelper::getNewsroomTopics());
        }
        // Compare taxonomy terms modified by pathauto with the current value
        // from the URL.
        if ($taxonomy_terms) {
          foreach ($taxonomy_terms as $term_item) {
            if (pathauto_cleanstring($term_item->name) == $request_name) {
              $taxonomy_term = $term_item;
              break;
            }
          }
        }
      }
      cache_set($cache_key, $taxonomy_term, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_term_from_request', 864000));
    }

    return $taxonomy_term;
  }

  /**
   * Defines whether the item is new or not.
   *
   * @param int $created
   *   Timestamp when item was created.
   * @param int $nid
   *   Node id.
   *
   * @return bool
   *   It is a new item or not.
   */
  public static function isNewItem($created, $nid) {
    return user_is_logged_in() && $created > time() - variable_get('newsroom_days_number_for_new_user', 14) * 86400 && !node_last_viewed($nid);
  }

  /**
   * Gets dropdown options for event types.
   *
   * @param bool $events_only
   *   Display only event types.
   *
   * @return array
   *   Drop down options array.
   */
  public static function getNewsroomTypeOptions($events_only = FALSE) {
    $type_options = NewsroomHelper::getTaxonomyTermOptions(NewsroomHelper::getNewsroomTypes());
    if ($events_only) {
      $events_types = NewsroomHelper::getEventsTermsIds();
      // Filter out non events type.
      foreach ($type_options as $key => $type_item) {
        if (!in_array($key, $events_types)) {
          unset($type_options[$key]);
        }
      }
    }
    $empty = array(t('- None -'));
    return $empty + $type_options;
  }

  /**
   * Gets dropdown options for newsroom topics.
   *
   * @param array $used_topics
   *   Used topics.
   *
   * @return array
   *   Drop down options array.
   */
  public static function getNewsroomTopicOptions($used_topics = array()) {
    $topic_options = NewsroomHelper::getTaxonomyTermOptions(NewsroomHelper::getNewsroomTopics());
    foreach ($topic_options as $key => $topic) {
      if (!in_array($key, $used_topics)) {
        unset($topic_options[$key]);
      }
    }
    $empty = array(t('- None -'));
    return $empty + $topic_options;
  }

  /**
   * Gets node ids associated with the topics.
   *
   * @param array $topic_ids
   *   Topics' array.
   *
   * @return array
   *   Array of nodes' ids.
   */
  public static function getNodeRelatedToTopic($topic_ids = array()) {
    $cache_key = 'get_node_related_to_topic:' . md5(implode('', $topic_ids));
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $query = db_select('field_data_field_newsroom_topics', 'ttopic');
      $query->addField('ttopic', 'entity_id');
      $query->condition('field_newsroom_topics_tid', $topic_ids);
      $query->groupBy('ttopic.entity_id');
      $query->having('count(ttopic.entity_id) = :cnt', array(':cnt' => count($topic_ids)));

      $data = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_node_related_to_topic', 3600));
    }
    return $data;
  }

  /**
   * Gets number of items per block for the current page.
   *
   * @param bool $is_highligted
   *   Is block highligted.
   *
   * @return int
   *   Number of items.
   */
  public static function getBlockItemsNumber($is_highligted) {
    $front_page = drupal_is_front_page();
    if ($is_highligted) {
      // Highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_highlighted_items' : 'newsroom_summary_block_num_highlighted_items';
    }
    else {
      // Not highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_items' : 'newsroom_summary_block_num_items';
    }
    return variable_get($variable_name, 5);
  }

  /**
   * Gets Universe Id.
   *
   * @return string
   *   Universe Id.
   */
  public static function getUniverseId() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $data = variable_get('newsroom_universe_id', FALSE);
    }
    return $data;
  }

  /**
   * Gets newsroom type vocabulary.
   *
   * @return object
   *   Newsroom type vocabulary.
   */
  public static function getNewsroomTypeVocabulary() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $data = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
    }
    return $data;
  }

  /**
   * Gets newsroom topic vocabulary.
   *
   * @return object
   *   Newsroom topic vocabulary.
   */
  public static function getNewsroomTopicVocabulary() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $data = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY);
    }
    return $data;
  }

  /**
   * Gets newsroom topics.
   *
   * @return array
   *   Newsroom topics.
   */
  public static function getNewsroomTopics() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $vocabulary = NewsroomHelper::getNewsroomTopicVocabulary();
      $data = NewsroomHelper::getNewsroomTaxonomyTerms($vocabulary->vid);
    }
    return $data;
  }

  /**
   * Gets Newsroom types.
   *
   * @return array
   *   Newsroom types.
   */
  public static function getNewsroomTypes() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $vocabulary = NewsroomHelper::getNewsroomTypeVocabulary();
      $data = NewsroomHelper::getNewsroomTaxonomyTerms($vocabulary->vid);
    }
    return $data;
  }

  /**
   * Gets translated taxonomy items from vocabulary.
   *
   * @param int $vocabulary_id
   *   Vocabulary ID.
   *
   * @return array
   *   Array of taxonomy terms.
   */
  protected static function getNewsroomTaxonomyTerms($vocabulary_id) {
    global $language;
    $cache_key = 'terms_' . $vocabulary_id . $language->language;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $data = i18n_taxonomy_get_tree($vocabulary_id, language_default()->language, 0, NULL, TRUE);
      foreach ($data as $key => $taxonomy_term) {
        $i18n_object = i18n_get_object('taxonomy_term', $taxonomy_term->tid);
        $data[$key] = $i18n_object->localize($language->language);
      }
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    }

    return $data;
  }

  /**
   * Gets newsroom type by id.
   *
   * @param int|null $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getNewsroomType($tid = NULL) {
    return $tid ? NewsroomHelper::findTermById(NewsroomHelper::getNewsroomTypes(), $tid) : NULL;
  }

  /**
   * Gets newsroom type by id.
   *
   * @param int|null $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getNewsroomTopic($tid = NULL) {
    return $tid ? NewsroomHelper::findTermById(NewsroomHelper::getNewsroomTopics(), $tid) : NULL;
  }

  /**
   * Finds term by id.
   *
   * @param array $taxonomy_terms
   *   Taxonomy terms array.
   * @param int $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function findTermById($taxonomy_terms, $tid) {
    $taxonomy_term = NULL;
    if ($taxonomy_terms) {
      foreach ($taxonomy_terms as $item) {
        if ($item->tid == $tid) {
          $taxonomy_term = $item;
        }
      }
    }
    return $taxonomy_term;
  }

  /**
   * Finds children by id.
   *
   * @param array $taxonomy_terms
   *   Taxonomy terms array.
   * @param int $parent_tid
   *   Parent taxonomy term ID.
   *
   * @return array
   *   Taxonomy terms.
   */
  public static function findChildrenById($taxonomy_terms, $parent_tid) {
    $children = array();
    if ($taxonomy_terms) {
      foreach ($taxonomy_terms as $item) {
        if (in_array($parent_tid, $item->parents)) {
          $children[$item->tid] = $item;
        }
      }
    }
    return $children;
  }

  /**
   * Returns newsroom URL.
   *
   * @param string $url_part
   *   Additional part of URL.
   *
   * @return string
   *   URL.
   */
  public static function getNewsroomUrl($url_part) {
    return NewsroomHelper::getUniverseUrl() . $url_part;
  }

  /**
   * Gets the enabled languages.
   *
   * @return array
   *   Languages array.
   */
  public static function getEnabledLanguages() {
    $lang_keys = &drupal_static(__FUNCTION__);
    if (!isset($lang_keys)) {
      $lang = locale_language_list();
      $lang_keys = array_keys($lang);
      $eng = array_search('en', $lang_keys);
      if ($eng) {
        unset($lang_keys[$eng]);
        array_unshift($lang_keys, 'en');
      }
    }
    return $lang_keys;
  }

  /**
   * Returns the current formated date.
   *
   * @param string $format
   *   Format string.
   * @param int $timestamp
   *   Timestamp.
   *
   * @return string
   *   Formated date string.
   */
  public static function getFormatedDate($format = 'Y-m-d', $timestamp = NULL) {
    $timestamp = !empty($timestamp) ? $timestamp : time();
    return format_date($timestamp, 'custom', $format);
  }

  /**
   * Deletes translations.
   *
   * @param object $entity
   *   Object : taxonomy term or node.
   * @param int $entity_id
   *   Entity id.
   * @param string|null $language
   *   Language string.
   */
  public static function deleteEntityTranslations($entity, $entity_id, $language = NULL) {
    $languages = $language ? array($language) : language_list();
    $handler = entity_translation_get_handler('node', $entity);

    foreach ($languages as $language) {
      // Delete translation for the current language.
      $handler->removeTranslation($language->language);
      field_attach_presave('node', $entity);
      field_attach_update('node', $entity);
    }

    if (module_exists('entitycache')) {
      cache_clear_all($entity_id, 'cache_entity_node');
    }
  }

  /**
   * Validates if a given newsroom universe exists.
   *
   * @param string $universe_id
   *   Newsroom Universe ID.
   *
   * @return bool
   *   Newsroom Universe exists or not.
   */
  public static function validateUniverse($universe_id = NULL) {
    if ($universe_id) {
      // logout.cfm is used because it is always available if a universe exists.
      $test = drupal_http_request(NewsroomHelper::getUniverseUrl() . '/logout.cfm');
      return $test->code == 200;
    }

    return FALSE;
  }

  /**
   * Validates if a given subsite exists.
   *
   * @param string $subsite
   *   Newsroom Universe subsite.
   *
   * @return bool
   *   Newsroom Universe subsite exists or not.
   */
  public static function validateSubsite($universe_id = NULL, $subsite = NULL) {
    // The subsite is not mandatory.
    if (empty($subsite)) {
      return TRUE;
    }
    else {
      if ($universe_id) {
        $test = drupal_http_request(NewsroomHelper::getUniverseUrl() . '?subsite=' . $subsite);
        return $test->code == 200;
      }
    }

    return FALSE;
  }

  /**
   * Gets taxonomy terms options.
   *
   * @param array $terms
   *   Taxonomy term arrays.
   *
   * @return array
   *   Dropdown options.
   */
  public static function getTaxonomyTermOptions($terms) {
    $options = array();
    if ($terms) {
      foreach ($terms as $term) {
        $options[$term->tid] = str_repeat('-', $term->depth) . $term->name;
      }
    }
    return $options;
  }

  /**
   * Gets IDs array from topics array.
   *
   * @return array
   *   Array of IDs.
   */
  public static function getPageUsedTopicsIds() {
    $cache_key = 'result_topics';
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $tids = $cache->data;
    }
    else {
      $query = db_select('node', 'n');
      $query->distinct();
      $query->fields('topic_field', array('tid' => 'field_newsroom_topics_tid'));
      $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
      $query->join('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
      $query->condition('n.status', 1);
      $tids = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $tids, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_page_result_topics', 86400));
    }
    return $tids;
  }

  /**
   * Get email hash for subscriptions.
   *
   * @param string $email
   *   E-mail.
   *
   * @return string
   *   Hash.
   */
  public static function getEmailHash($email) {
    return md5($email . variable_get('newsroom_app_key'));
  }

  /**
   * Gets the node title without loading the whole node object.
   *
   * @param int $nid
   *   Node nid.
   *
   * @return string
   *   Node title.
   */
  public static function getNodeTitle($nid) {
    $cache_key = 'newsroom:node_title:' . $nid;
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $node_title = $cache->data;
    }
    else {
      $node_title = db_query('SELECT title_field_value FROM {field_data_title_field} WHERE entity_id = :nid', array(':nid' => $nid))->fetchField();
      if (empty($node_title)) {
        $node_title = db_query('SELECT title FROM {node} WHERE nid = :nid', array(':nid' => $nid))->fetchField();
      }
      cache_set($cache_key, $node_title, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_node_title', 3600));
    }
    return $node_title;
  }

  /**
   * Gets entity value for non transltable fields.
   *
   * @param object $entity
   *   Entity object.
   * @param string $field_name
   *   Field name.
   * @param string $value_name
   *   Name of value field.
   *
   * @return string|int|null
   *   Field value.
   */
  public static function getFieldValue($entity, $field_name, $value_name = 'value') {
    $value = NULL;

    if ($entity) {
      if (isset($entity->{$field_name}[LANGUAGE_NONE][0][$value_name])) {
        if (count($entity->{$field_name}[LANGUAGE_NONE]) > 1) {
          $value = array();
          foreach ($entity->{$field_name}[LANGUAGE_NONE] as $item) {
            $value[] = $item[$value_name];
          }
        }
        else {
          $value = $entity->{$field_name}[LANGUAGE_NONE][0][$value_name];
        }
      }
    }

    return $value;
  }

  /**
   * Gets main URL for a node based on the newsroom type settings.
   *
   * @param object $node
   *   Node object.
   * @param string $display_name
   *   Display name.
   *
   * @return string
   *   Main node URL.
   */
  public static function getNodeMainUrl($node, $display_name = NULL) {
    $url = 'node/' . $node->nid;
    $type = NewsroomHelper::getNewsroomType(NewsroomHelper::getFieldValue($node, 'field_newsroom_item_type', 'tid'));
    $click_through = NewsroomHelper::getFieldValue($type, 'field_newsroom_direct_link');
    $main_link_url = NewsroomHelper::getFieldTranslatedValue($node, 'field_newsroom_item_main_link', 'url');

    if (!empty($main_link_url)) {
      if ($click_through == NEXTEUROPA_NEWSROOM_CLICKTHROUGH_FORCE) {
        $url = $main_link_url;
      }
      elseif (NewsroomHelper::getFieldValue($node, 'field_newsroom_teaser_only')) {
        // If item is Teaser only.
        switch ($click_through) {
          case 'always':
            $url = $main_link_url;
            break;

          case 'from_teaser':
            if ($display_name == 'teaser') {
              $url = $main_link_url;
            }
            break;
        }
      }
    }

    return $url;
  }

  /**
   * Gets translated field value.
   *
   * @param object $entity
   *   Entity object.
   * @param string $field_name
   *   Field name.
   * @param string $property_name
   *   Field property name.
   * @param string $entity_type
   *   Entity type.
   *
   * @return int|string|null
   *   Field value.
   */
  public static function getFieldTranslatedValue($entity, $field_name, $property_name = 'value', $entity_type = 'node') {
    $field = field_view_field($entity_type, $entity, $field_name);
    $value = NULL;
    if (isset($field['#items'][0]['safe_value'])) {
      $value = $field['#items'][0]['safe_value'];
    }
    elseif (isset($field['#items'][0][$property_name])) {
      $value = $field['#items'][0][$property_name];
    }
    return $value;
  }

  /**
   * Checks date format and if it is ok returns DateTime object.
   *
   * @param string $value
   *   Date string.
   * @param string $regex
   *   Regular expression.
   *
   * @return \DateTime|null
   *   Datetime or NULL.
   */
  public static function checkDateFormat($value, $regex = '/^\d{2}-\d{2}-\d{4}$/') {
    $date = NULL;
    if (preg_match($regex, $value)) {
      $date = new DateTime();
      $date->setTimestamp(strtotime($value));
    }
    return $date;
  }

}
