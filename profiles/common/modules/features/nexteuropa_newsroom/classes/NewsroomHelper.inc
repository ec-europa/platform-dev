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
   * @return string
   *   Newsroom URL.
   */
  public static function getNewsroomPageUrl() {
    return 'newsroom/' . implode('/', func_get_args());
  }

  /**
   * Generates newsroom agenda URL.
   *
   * @return string
   *   Newsroom agenda URL.
   */
  public static function getNewsroomAgendaUrl() {
    return 'newsroom-agenda/' . implode('/', func_get_args());
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
   * @param string $url
   *   RSS feed URL to call.
   * @param string $importer_id
   *   Importer ID.
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
   * Restores default URL of importer.
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
      $url = NewsroomHelper::getNewsroomUrl(NEXTEUROPA_NEWSROOM_TOPIC_FULL);
    }

    if ($importer_id == NEXTEUROPA_NEWSROOM_TYPE_IMPORTER) {
      $url = NewsroomHelper::getNewsroomUrl(NEXTEUROPA_NEWSROOM_TYPE_FULL);
    }

    if ($importer_id == NEXTEUROPA_NEWSROOM_ITEM_IMPORTER) {
      $url = NewsroomHelper::getNewsroomUrl(NEXTEUROPA_NEWSROOM_ITEM_FULL);
    }

    return $url;
  }

  /**
   * Gets newsroom item by original newsroom Id.
   *
   * @param int $newsroom_id
   *   Newsroom original ID.
   *
   * @return nid
   *   Node id for newsroom item.
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
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
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
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
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
            if ($a->p1 == $b->p1) {
              if ($a->p2 == $b->p2) {
                if ($a->p3 == $b->p3) {
                  if ($a->p4 == $b->p4) {
                    if ($a->p5 == $b->p5) {
                      if ($a->p6 == $b->p6) {
                        if ($a->p7 == $b->p7) {
                          if ($a->p8 == $b->p8) {
                            if ($a->p9 == $b->p9) {
                              if ($a->plid == $b->plid) {
                                if ($a->weight == $b->weight) {
                                  if ($a->mlid == $b->mlid) {
                                    return 0;
                                  }
                                  else {
                                    return $a->mlid < $b->mlid ? -1 : 1;
                                  }
                                }
                                else {
                                  return $a->weight < $b->weight ? -1 : 1;
                                }
                              }
                              else {
                                return $a->plid < $b->plid ? -1 : 1;
                              }
                            }
                            else {
                              return $a->p9 < $b->p9 ? -1 : 1;
                            }
                          }
                          else {
                            return $a->p8 < $b->p8 ? -1 : 1;
                          }
                        }
                        else {
                          return $a->p7 < $b->p7 ? -1 : 1;
                        }
                      }
                      else {
                        return $a->p6 < $b->p6 ? -1 : 1;
                      }
                    }
                    else {
                      return $a->p5 < $b->p5 ? -1 : 1;
                    }
                  }
                  else {
                    return $a->p4 < $b->p4 ? -1 : 1;
                  }
                }
                else {
                  return $a->p3 < $b->p3 ? -1 : 1;
                }
              }
              else {
                return $a->p2 < $b->p2 ? -1 : 1;
              }
            }
            else {
              return $a->p1 < $b->p1 ? -1 : 1;
            }
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
   * Gets events Terms ids.
   *
   * @return array
   *   Newsroom type taxonomy terms array.
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
   *   Taxonomy terms
   */
  public static function getGroupTypeTerms($selected = array()) {
    $cache_key = 'newsroom:group_types:' . implode('-', $selected);
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $terms = $cache->data;
    }
    else {
      $terms = NewsroomHelper::getNewsroomTypes();
      foreach ($terms as $key => $term) {
        $test = i18n_get_object('taxonomy_term', $term->tid);
        if (!in_array($term->tid, $selected)) {
          $terms[$key] = $test->get_object();
        }
      }
      cache_set($cache_key, $terms, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_group_types', 3600));
    }

    return $terms;
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
      $data = NEXTEUROPA_NEWSROOM_URL . NewsroomHelper::getUniverseId() . '/';
    }
    return $data;
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
      $field_name = 'field_associated_newsroom_' . $type;
      $mappings = field_info_field_map();
      if (isset($mappings[$field_name]['bundles']['node'])) {
        $instances = $mappings[$field_name]['bundles']['node'];
      }
    }
    return $instances;
  }

  /**
   * Term ids of item types to be used in agenda.
   *
   * @return array
   *   Taxonomy term ids
   */
  public static function getTermsFromVocabularies($vocabularies = array()) {
    $taxonomy_terms = array();
    foreach ($vocabularies as $vocabulary_name) {
      if ($vocabulary_name == NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY) {
        $taxonomy_terms = array_merge($taxonomy_terms, NewsroomHelper::getNewsroomTypes());
      }
      if ($vocabulary_name == NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY) {
        $taxonomy_terms = array_merge($taxonomy_terms, NewsroomHelper::getNewsroomTopics());
      }
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
   *
   * @return object
   *   Taxonomy term.
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
            $term_item->name = NewsroomHelper::getTermTranslatedName($term_item);
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
    return user_is_logged_in() && $created > time() - variable_get('newsroom_days_number_for_new_user', 14) * 86400 && !node_last_viewed($nid);
  }

  /**
   * Get dropdown options for event types.
   *
   * @return array
   *   Drop down options array.
   */
  public static function getNewsroomTypeEventsOptions() {
    $type_options = NewsroomHelper::getTaxonomyTermOptions(NewsroomHelper::getNewsroomTypes());
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
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_node_related_to_topic', 3600));
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

  /**
   * Helper function to check if the universe ID has been already set.
   *
   * @param int $newsroom_universe_id
   *   Newsroom Universe ID.
   *
   * @return array
   *   Newsroom Universe ID info.
   */
  public static function getUniverseIdInputInfo($newsroom_universe_id = NULL) {
    // After initital setup disable Universe ID field.
    $universe_id = array();
    if (!empty($newsroom_universe_id)) {
      $universe_id['disabled'] = TRUE;
      $universe_id['description'] = t('To change the Newsroom Universe ID contact the site administrator.');
      $universe_id['class'] = 'selected';
      $universe_id['collapsing'] = FALSE;
    }
    else {
      $universe_id['disabled'] = FALSE;
      $universe_id['description'] = t('After setting the Newsroom Universe ID for the first time content will be imported from the Newsroom service. This might take a few minutes.');
      $universe_id['class'] = 'not-selected';
      $universe_id['collapsing'] = TRUE;
    }
    return $universe_id;
  }

  /**
   * Gets UniverseId.
   *
   * @return string
   *   UniverseId
   */
  public static function getUniverseId() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $data = variable_get('newsroom_universe_id', FALSE);
    }
    return $data;
  }

  /**
   * Gets Newsroom Type Vocabulary.
   *
   * @return object
   *   Newsroom Type Vocabulary.
   */
  public static function getNewsroomTypeVocabulary() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $data = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
    }
    return $data;
  }

  /**
   * Gets Newsroom Topic Vocabulary.
   *
   * @return object
   *   Newsroom Topic Vocabulary.
   */
  public static function getNewsroomTopicVocabulary() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $data = taxonomy_vocabulary_machine_name_load(NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY);
    }
    return $data;
  }

  /**
   * Gets Newsroom topics.
   *
   * @return array
   *   Newsroom topics.
   */
  public static function getNewsroomTopics() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $cache_key = 'topics';
      $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
      if ($cache) {
        $data = $cache->data;
      }
      else {
        $vocabulary = NewsroomHelper::getNewsroomTopicVocabulary();
        $data = taxonomy_get_tree($vocabulary->vid, 0, NULL, TRUE);
        cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
      }
    }
    return $data;
  }

  /**
   * Gets Newsroom types.
   *
   * @return array
   *   Newsroom topics.
   */
  public static function getNewsroomTypes() {
    $data = &drupal_static(__FUNCTION__);
    if (!isset($data)) {
      $cache_key = 'types';
      $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
      if ($cache) {
        $data = $cache->data;
      }
      else {
        $vocabulary = NewsroomHelper::getNewsroomTypeVocabulary();
        $data = taxonomy_get_tree($vocabulary->vid, 0, NULL, TRUE);
        cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
      }
    }
    return $data;
  }

  /**
   * Gets Newsroom type by id.
   *
   * @param int $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getNewsroomType($tid) {
    $types = NewsroomHelper::getNewsroomTypes();
    return NewsroomHelper::findTermById($types, $tid);
  }

  /**
   * Gets Newsroom type by id.
   *
   * @param int $tid
   *   Taxonomy term ID.
   *
   * @return object
   *   Taxonomy term.
   */
  public static function getNewsroomTopic($tid) {
    $topics = NewsroomHelper::getNewsroomTypes();
    return NewsroomHelper::findTermById($topics, $tid);
  }

  /**
   * Finds term by id.
   *
   * @param array $taxonomy_terms
   *   Taxonomy terms array.
   *
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
   *
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
   * Helper function to delete translations.
   *
   * @param object $entity
   *   Object : taxonomy term or node.
   * @param int $entity_id
   *   Entity id.
   * @param string $lang
   *   Language string.
   */
  public static function deleteEntityTranslations($entity, $entity_id, $lang = FALSE) {
    $languages = !$lang ? language_list() : array($lang);
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
   * Validate if a given Newsroom Universe exists.
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
      $test = drupal_http_request(NEXTEUROPA_NEWSROOM_URL . $universe_id . '/logout.cfm');
      return $test->code == 200;
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

}
