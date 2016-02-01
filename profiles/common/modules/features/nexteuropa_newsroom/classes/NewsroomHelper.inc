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
    } else {
      // Get a list of the existing content type.
      $content_types = node_type_get_types();
      // Exclude the ct used for the import.
      unset($content_types[NEWSROOM_CONTENT_TYPE]);
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
    // Load the Feeds Source object.
    $source = feeds_source($importer_id);
    $config = $source->getConfig();
    // @TODO deal with the case if we don't have an item setup.
    $additional_config = array(
      'FeedsHTTPFetcher' => array(
        'source' => $url,
      ),
    );
    $source->setConfig(array_merge($config, $additional_config));
    // Make sure we force the import of the item.
    $processor_config = $source->importer->processor->getConfig();
    $source->importer->processor->setConfig(array_merge($processor_config, $additional_config));
    $source->import();
    $source->delete();
  }

  /**
   * Get newsroom item by Id.
   */
  public static function getNodeByNewsroomItemId($newsroom_id = 0) {
    $newsroom_data = &drupal_static(__FUNCTION__);
    $cache_key = 'newsroom_item_by_id:' . $newsroom_id;
    if (!isset($newsroom_data)) {
      $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
      if ($cache) {
        $newsroom_data = $cache->data;
      } else {
        $query = new EntityFieldQuery();
        $newsroom_item = $query
          ->entityCondition('entity_type', 'node')
          ->fieldCondition('field_newsroom_item_id', 'value', $newsroom_id, '=')
          ->execute();
        $newsroom_data = isset($newsroom_item['node']) ? $newsroom_item['node'] : FALSE;
        cache_set($cache_key, $newsroom_data, NEWSROOM_CACHE_TABLE, time() + 3600);
      }
    }
    return $newsroom_data;
  }

  /**
   * Finds a menu item for a given path.
   */
  public static function getMenuByPath($path) {
    $cache_key = 'get_menu_by_path' . md5($path);
    $cache = cache_get($cache_key);
    if ($cache) {
      $data = $cache->data;
    } else {
      $query = db_select('menu_links', 'ml')
        ->fields('ml')
        ->condition('ml.link_path', $path)
        ->execute();
      $data = NewsroomHelper::convertPdoToArray($query);
      cache_set($cache_key, $data);
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
    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $data = $cache->data;
    } else {
      $query = db_select('field_data_field_associated_newsroom_topic', 'f')
        ->fields('f')
        ->condition('f.field_associated_newsroom_topic_tid', $topic_ids)
        ->execute();
      $data = NewsroomHelper::convertPdoToArray($query);

      cache_set($cache_key, $data, NEWSROOM_CACHE_TABLE);
    }
    return $data;
  }

  /**
   * Active menu for newsroom items.
   *
   * Returns wich menu item should be active for a newsroom item
   * based on the assigned topics.
   */
  public static function fetchActiveMenu($topic_id) {
    $path = FALSE;

    // Check if they are added to menu.
    $menu_items = array();
    // Fetch enities associated to topic using the special field.
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
        } elseif ($a['router_path'] == 'node/%' && $b['router_path'] == 'taxonomy/term/%') {
          return 1;
        } else {
          if ($a['plid'] == $b['plid']) {
            if ($a['weight'] == $b['weight']) {
              if ($a['mlid'] == $b['mlid']) {
                return 0;
              } else {
                return $a['mlid'] < $b['mlid'] ? -1 : 1;
              }
            } else {
              return $a['weight'] < $b['weight'] ? -1 : 1;
            }
          } else {
            return $a['plid'] < $b['plid'] ? -1 : 1;
          }
        }
      });

      $menu_item_link = array_shift($menu_items);
      $path = $menu_item_link['link_path'];
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
    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $term_ids = $cache->data;
    } else {
      $term_ids = NULL;
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

      cache_set($cache_key, $term_ids, NEWSROOM_CACHE_TABLE);
    }
    return $term_ids;
  }

  public static function getEventsTermsIds() {
    return NewsroomHelper::getTaxonomyTermFromField('field_newsroom_type', array('consultation_funding', 'events', 'agenda'), NEWSROOM_TYPE_VOCABULARY);
  }

  /**
   * Item types or Collection to group by.
   *
   * @return array
   *   Terms
   */
  public static function getGroupTypeTerms($selected = array()) {
    $cache_key = 'newsroom:group_types:' . implode('-', $selected);
    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $terms = $cache->data;
    } else {
      $newsroom_type_vocabulary = taxonomy_vocabulary_machine_name_load(NEWSROOM_TYPE_VOCABULARY);
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
      cache_set($cache_key, $terms, NEWSROOM_CACHE_TABLE, time() + 3600);
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
    return NEWSROOM_URL . $universe_id . '/';
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
    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $taxonomy_terms = $cache->data;
    } else {
      $query = db_select('taxonomy_term_data', 'td');
      $query->leftJoin('taxonomy_vocabulary', 'tv', 'td.vid = tv.vid');
      $query->fields('td');
      $query->fields('tv', array('machine_name'));
      $query->condition('tv.machine_name', $vocabularies);
      $taxonomy_terms = NewsroomHelper::convertPdoToArray($query->execute());

      cache_set($cache_key, $taxonomy_terms, NEWSROOM_CACHE_TABLE, time() + 3600);
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
    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $taxonomy_term = $cache->data;
    } else {
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

      cache_set($cache_key, $taxonomy_term, NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $taxonomy_term;
  }
  
  public static function getTermTranslatedName($taxonomy_term) {
    global $language;
    $curr_lang = $language->language;
    $translation = field_get_items('taxonomy_term', $taxonomy_term, 'name_field', $curr_lang);
    return $translation ? $translation[0]['safe_value'] : $taxonomy_term->name;
  }

}
