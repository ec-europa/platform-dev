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
   * Merges a term_tid and its children into one array.
   *
   * @param int $term_tid
   *   Term id.
   * @param int $term_vid
   *   Vid id.
   *
   * @return array.
   *   tids
   */
  public static function getTermChildren($term_tid, $term_vid = NULL) {
    // We need parent ID also in the output array to use it in query.
    $parent_children_tids = array($term_tid);
    $children_tids = array_keys(taxonomy_get_children($term_tid, $term_vid));
    if (count($children_tids) > 0) {
      $parent_children_tids = array_merge($parent_children_tids, $children_tids);
    }

    return $parent_children_tids;
  }

  /**
   * Helper function to serialize PDO object into an array.
   */
  public static function convertPdoToArray($query) {
    $data = array();
    if ($query) {
      while ($result = $query->fetchAssoc()) {
        $data[] = $result;
      }
    }

    return $data;
  }

  /**
   * Returns newsroom URL.
   *
   * @return string
   *   Newsroom URL.
   */
  public static function getNewsroomUrl() {
    return 'newsroom/' . implode('/', func_get_args());
  }

  /**
   * Returns newsroom agenda URL.
   *
   * @return string
   *   Newsroom agenda URL.
   */
  public static function getNewsroomAgendaUrl() {
    return 'newsroom-agenda/' . implode('/', func_get_args());
  }

  /**
   * Prepare options for the content type select.
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
   * Call newsroom items import with the certain URL.
   *
   * @param string $url
   *   URL to call.
   */
  public static function runFeedImporter($url, $importer_id) {
    $source = feeds_source($importer_id);
    $config = $source->getConfig();
    $config['FeedsHTTPFetcher']['source'] = $url;
    $source->setConfig($config);
    $source->import();
    // Restore the default URL in order to run importers manually or via cron.
    $config['FeedsHTTPFetcher']['source'] = NewsroomHelper::restoreFeedImporter($importer_id);
    $source->setConfig($config);
    $source->save();
  }

  /**
   * Restore default URL of importer.
   *
   * @param string $importer_id
   *   Importer ID.
   *
   * @return string
   *   URL.
   */
  public static function restoreFeedImporter($importer_id) {
    $url = '';
    if ($importer_id == NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER || $importer_id == NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER) {
      $url = NewsroomHelper::buildImportUrl(NEXTEUROPA_NEWSROOM_TOPIC_FULL);
    }

    if ($importer_id == NEXTEUROPA_NEWSROOM_TYPE_IMPORTER) {
      $url = NewsroomHelper::buildImportUrl(NEXTEUROPA_NEWSROOM_TYPE_FULL);
    }

    if ($importer_id == NEXTEUROPA_NEWSROOM_ITEM_IMPORTER) {
      $url = NewsroomHelper::buildImportUrl(NEXTEUROPA_NEWSROOM_ITEM_FULL);
    }

    return $url;
  }

  /**
   * Builds import url.
   *
   * @param string $url_part
   *   Part of URL.
   *
   * @return string
   *   URL.
   */
  public static function buildImportUrl($url_part) {
    global $_newsroom_universe_url;
    return $_newsroom_universe_url . $url_part;
  }

  /**
   * Get newsroom item by Id.
   */
  public static function getNodeByNewsroomItemId($newsroom_id = 0) {
    $newsroom_data = &drupal_static(__FUNCTION__);
    $cache_key = 'newsroom_item_by_id:' . $newsroom_id;
    if (!isset($newsroom_data)) {
      $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
      if ($cache) {
        $newsroom_data = $cache->data;
      }
      else {
        $query = new EntityFieldQuery();
        $newsroom_item = $query
          ->entityCondition('entity_type', 'node')
          ->fieldCondition('field_newsroom_item_id', 'value', $newsroom_id, '=')
          ->execute();
        $newsroom_data = isset($newsroom_item['node']) ? $newsroom_item['node'] : FALSE;
        cache_set($cache_key, $newsroom_data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
      }
    }
    return $newsroom_data;
  }

  /**
   * Finds a menu item for a given path.
   */
  public static function getMenuByPath($path) {
    $cache_key = 'get_menu_by_path' . md5($path);
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $data = $cache->data;
    }
    else {
      $query = db_select('menu_links', 'ml')
        ->fields('ml')
        ->condition('ml.link_path', $path)
        ->execute();
      $data = NewsroomHelper::convertPdoToArray($query);
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    }
    return $data;
  }

  /**
   * Helper to retrieve a mlid for a given path.
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
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $data = $cache->data;
    }
    else {
      $query = db_select('field_data_field_associated_newsroom_topic', 'f')
        ->fields('f')
        ->condition('f.field_associated_newsroom_topic_tid', $topic_ids)
        ->execute();
      $data = NewsroomHelper::convertPdoToArray($query);

      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    }
    return $data;
  }

  /**
   * Get combined node newsroom topics.
   *
   * @param object $node_wrapper
   *   Node wrapper.
   *
   * @return array
   *   Newsroom topics.
   */
  public static function getNodeTopics($node_wrapper) {
    $nid = $node_wrapper->__isset('nid') ? $node_wrapper->nid->value() : NULL;
    $cache_key = 'get_node_topics:' . $nid;
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $topics = $cache->data;
    }
    else {
      $primary_topics = $node_wrapper->__isset('field_primary_topic') ? $node_wrapper->field_primary_topic->value() : NULL;
      if (!empty($primary_topics)) {
        $primary_topics = !is_array($primary_topics) ? array($primary_topics) : $primary_topics;
      }
      else {
        $primary_topics = array();
      }

      // Get regular topics.
      $topics = $node_wrapper->__isset('field_newsroom_topics') ? $node_wrapper->field_newsroom_topics->value() : NULL;
      if (!empty($topics)) {
        $topics = !is_array($topics) ? array($topics) : $topics;
      }
      else {
        $topics = array();
      }

      $topics = array_merge($primary_topics, $topics);

      cache_set($cache_key, $topics, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    }
    return $topics;
  }

  /**
   * Active menu for newsroom items.
   *
   * Returns wich menu item should be active for a newsroom item
   * based on the assigned topics.
   */
  public static function fetchActiveMenu($topic_id) {
    $cache_key = 'fetch_active_menu' . $topic_id;
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
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
          // Could use entity_uri() but we would have to load the full entity...
          $menu_link_items = NewsroomHelper::getMenuByPath(str_replace('_', '/', $entity['entity_type']) . '/' . $entity['entity_id']);

          if ($menu_link_items !== FALSE) {
            foreach ($menu_link_items as $menu_item) {
              $menu_items[] = $menu_item;
            }
          }
        }
      }

      if (count($menu_items) > 0) {
        // Favor terms over nodes and lower entity ID in case we have multiple.
        usort($menu_items, function ($a, $b) {
          if ($a['router_path'] == 'taxonomy/term/%' && $b['router_path'] == 'node/%') {
            return -1;
          }
          elseif ($a['router_path'] == 'node/%' && $b['router_path'] == 'taxonomy/term/%') {
            return 1;
          }
          else {
            if ($a['plid'] == $b['plid']) {
              if ($a['weight'] == $b['weight']) {
                if ($a['mlid'] == $b['mlid']) {
                  return 0;
                }
                else {
                  return $a['mlid'] < $b['mlid'] ? -1 : 1;
                }
              }
              else {
                return $a['weight'] < $b['weight'] ? -1 : 1;
              }
            }
            else {
              return $a['plid'] < $b['plid'] ? -1 : 1;
            }
          }
        });

        $menu_item_link = array_shift($menu_items);
        $path = $menu_item_link['link_path'];
      }

      cache_set($cache_key, $path, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    }

    return $path;
  }

  /**
   * Try to resolve each taxonomy term with a corresponding ID to map.
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
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
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
   * Get events Terms ids.
   */
  public static function getEventsTermsIds() {
    return NewsroomHelper::getTaxonomyTermFromField('field_newsroom_type',
      array(
        'consultation_funding',
        'events',
        'agenda',
      ), NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
  }

  /**
   * Item types or Collection to group by.
   *
   * @return array
   *   Terms
   */
  public static function getGroupTypeTerms($selected = array()) {
    $cache_key = 'newsroom:group_types:' . implode('-', $selected);
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $terms = $cache->data;
    }
    else {
      $newsroom_type_vocabulary = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
      $terms = array();
      if (is_object($newsroom_type_vocabulary) && $newsroom_type_vocabulary !== FALSE) {
        $terms = taxonomy_get_tree($newsroom_type_vocabulary->vid, 0, 1, TRUE);
        foreach ($terms as $key => $term) {
          $test = i18n_get_object('taxonomy_term', $term->tid);
          if (!in_array($term->tid, $selected)) {
            $terms[$key] = $test->get_object();
          }
        }
      }
      cache_set($cache_key, $terms, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }

    return $terms;
  }

  /**
   * Returns universe URL.
   *
   * @param string $universe_id
   *   Unique universe ID.
   *
   * @return string
   *   Universe URL.
   */
  public static function getUniverseUrl($universe_id) {
    return NEXTEUROPA_NEWSROOM_URL . $universe_id . '/';
  }

  /**
   * Get the existing instances of fields.
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
      $content_types = node_type_get_types();
      $field_name = 'field_associated_newsroom_' . $type;
      $instances = array();
      // We loop through the list of content types to find all the instances.
      foreach ($content_types as $machine_name => $content_type) {
        $exist = field_info_instance('node', $field_name, $machine_name);
        if ($exist !== NULL) {
          $instances[] = $exist['bundle'];
        }
      }
    }
    return $instances;
  }

  /**
   * Term ids of item types to be used in agenda.
   *
   * @return array
   *   tids
   */
  public static function getTermsFromVocabularies($vocabularies = array()) {
    $cache_key = 'newsroom:vocabulary_terms:' . md5(implode('', $vocabularies));
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $taxonomy_terms = $cache->data;
    }
    else {
      $query = db_select('taxonomy_term_data', 'td');
      $query->leftJoin('taxonomy_vocabulary', 'tv', 'td.vid = tv.vid');
      $query->fields('td');
      $query->fields('tv', array('machine_name'));
      $query->condition('tv.machine_name', $vocabularies);
      $taxonomy_terms = NewsroomHelper::convertPdoToArray($query->execute());
      cache_set($cache_key, $taxonomy_terms, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $taxonomy_terms;
  }

  /**
   * Try to get taxonomy URL part (taxonomy term name).
   *
   * @param string $request_name
   *   URL request part.
   * @param array $vocabularies
   *   List of vocabularies.
   */
  public static function getTermFromRequest($request_name, $vocabularies) {
    $cache_key = 'newsroom:term_from_request:' . md5($request_name);
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $taxonomy_term = $cache->data;
    }
    else {
      $taxonomy_term = NULL;
      if (is_int($request_name)) {
        $taxonomy_term = taxonomy_term_load($request_name);
      }

      if (!$taxonomy_term && count($vocabularies) > 0) {
        $taxonomy_terms = NewsroomHelper::getTermsFromVocabularies($vocabularies);
        // Compare taxonomy terms modified by pathauto with the current value
        // from the URL.
        if ($taxonomy_terms) {
          foreach ($taxonomy_terms as $term_item) {
            // Replace the name with translated value.
            $fullterm = taxonomy_term_load($term_item['tid']);
            $term_item['name'] = NewsroomHelper::getTermTranslatedName($fullterm);
            if (pathauto_cleanstring($term_item['name']) == $request_name) {
              $taxonomy_term = $fullterm;
              break;
            }
          }
        }
      }
      cache_set($cache_key, $taxonomy_term, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $taxonomy_term;
  }

  /**
   * Gets translated taxonomy term name.
   *
   * @param object $taxonomy_term
   *   Taxonomy term object.
   *
   * @return string
   *   The name of taxonomy term.
   */
  public static function getTermTranslatedName($taxonomy_term) {
    global $language;
    $curr_lang = $language->language;
    $translation = field_get_items('taxonomy_term', $taxonomy_term, 'name_field', $curr_lang);
    return $translation ? $translation[0]['safe_value'] : $taxonomy_term->name;
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
    return user_is_logged_in() && $created > time() - 14 * 86400 && !node_last_viewed($nid);
  }

  /**
   * Get dropdown options for event types.
   *
   * @return array
   *   Drop down options array.
   */
  public static function getNewsroomTypeEventsOptions() {
    $temp = new stdClass();
    $temp->type = NEXTEUROPA_NEWSROOM_CONTENT_TYPE;
    node_object_prepare($temp);

    $field_instance = field_info_instance('node', 'field_newsroom_item_type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    $field = field_info_field('field_newsroom_item_type');
    $type_options = taxonomy_options_list($field, $field_instance, 'node', $temp);

    $events_types = NewsroomHelper::getEventsTermsIds();

    // Filter out non events type.
    foreach ($type_options as $key => $type_item) {
      if (!in_array($key, $events_types)) {
        unset($type_options[$key]);
      }
    }

    $empty = array(t('- None -'));
    return $empty + $type_options;
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
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $data = $cache->data;
    }
    else {
      $query = db_select('field_data_field_newsroom_topics', 'ttopic');
      $query->addField('ttopic', 'entity_id');
      $query->condition('field_newsroom_topics_tid', $topic_ids);
      $query->groupBy('ttopic.entity_id');
      $query->having('count(ttopic.entity_id) = :cnt', array(':cnt' => count($topic_ids)));

      $data = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $data;
  }

  /**
   * Gets number of items per block for the current page.
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

}
