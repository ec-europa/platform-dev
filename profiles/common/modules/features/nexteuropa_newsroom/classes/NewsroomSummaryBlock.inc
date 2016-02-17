<?php

/**
 * @file
 * Code for the NewsroomBlock class.
 */

/**
 * NewsroomBlock class base class.
 */
class NewsroomSummaryBlock {

  protected $types = array();
  protected $topics = array();
  protected $operator = 'OR';

  /**
   * Getter.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Setter.
   */
  public function setTopics($value) {
    return $this->topics = $value;
  }

  /**
   * Setter.
   */
  public function setTypes($value) {
    return $this->types = $value;
  }

  /**
   * Getter.
   */
  public function getTypes() {
    return $this->types;
  }

  /**
   * Getter.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Setter.
   */
  public function setOperator($value) {
    return $this->operator = $value;
  }

  /**
   * Generates RSS link based on topics.
   *
   * @return string
   *   RSS link.
   */
  protected function generateRss() {
    $topics = $this->getTopics();
    $url_parts = array();
    $names = array();

    if (count($topics) > 0) {
      foreach ($topics as $topic_item) {
        $url_parts[] = $topic_item->tid;
        $names[] = $topic_item->name;
      }
    }
    else {
      $url_parts[] = 'all';
    }

    $rss_path = NewsroomHelper::getNewsroomUrl('all', implode('+', $url_parts), 'feed');
    $rss_title = count($names) ? 'RSS feed : ' . implode(', ', $names) : 'RSS feed';

    $rss = '<div class="newsroom_rss">';
    $rss .= theme('feed_icon', array(
      'url' => $rss_path,
      'title' => $rss_title,
    ));
    $rss .= l($rss_title, $rss_path);
    $rss .= '</div>';

    return $rss;
  }

  /**
   * Get filters: type, topics based on the request.
   */
  protected function getFilters() {
    $path = md5(current_path());
    $cache_key = 'newsroom:summary_filter:' . $path;
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);

    if ($cache) {
      $config = $cache->data;
    }
    else {
      $topic_operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;
      $selected_topics = array();
      $selected_types = array();

      $entity = $this->getEntityFromRequest();
      if ($entity) {
        if ($entity->type == 'newsroom_selection') {

          if (!empty($entity->field_newsroom_topic_operator)) {
            $topic_operator = $entity->field_newsroom_topic_operator['und'][0]['value'];
          }

          // Get topics from newsroom selection.
          $topic_config = field_get_items('node', $entity, 'field_selected_topics');
          $selected_topics = array();
          if ($topic_config) {
            foreach ($topic_config as $term_ref) {
              $selected_topics[] = $term_ref['target_id'];
            }
          }

          // Get types from newsroom selection.
          $type_config = field_get_items('node', $entity, 'field_selected_types');
          if ($type_config) {
            foreach ($type_config as $term_ref) {
              $selected_types[] = $term_ref['tid'];
            }
          }
        }
        elseif (isset($entity->field_associated_newsroom_topic) && !empty($entity->field_associated_newsroom_topic)) {
          // If it has the associated field, try to load topic.
          $selected_topics = array($entity->field_associated_newsroom_topic['und'][0]['tid']);
        }
      }

      $config['topic'] = count($selected_topics) > 0 ? taxonomy_term_load_multiple($selected_topics) : array();
      $config['topic_operator'] = $topic_operator;
      $config['type'] = NewsroomHelper::getGroupTypeTerms($selected_types);

      cache_set($cache_key, $config, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }

    $this->setTopics($config['topic']);
    $this->setTypes($config['type']);
    $this->setOperator($config['topic_operator']);
    $this->getOperator($config['topic_operator']);
  }

  /**
   * Tries to find the entity based on request.
   *
   * @return object
   *   Drupal entity: node, taxonomy term.
   */
  protected function getEntityFromRequest() {
    $entity = NULL;
    $current_path = menu_get_item();
    // We are on a view object, it's a term argument,
    // let's use to filter results.
    if ($current_path['page_callback'] === 'views_page' && $current_path['path'] === 'taxonomy/term/%') {
      $argument_values = array_values($current_path['page_arguments']);
      $last_argument_element = end($argument_values);
      // We may have a term page, let's try to load it.
      if (is_numeric($last_argument_element)) {
        $entity = taxonomy_term_load($last_argument_element);
      }
    }
    elseif ($current_path['page_callback'] === 'node_page_view') {
      // It is a node page take node entity from request.
      $entity = $current_path['map'][1];
    }
    elseif (isset($current_path['page_arguments'][0]->tid)) {
      // It's taxonomy term without views.
      $entity = $current_path['page_arguments'][0];
    }

    // Check if selection config is set.
    if (isset($entity->field_associated_newsroom_select) && !empty($entity->field_associated_newsroom_select)) {
      // If it has the selection field, try to load config.
      $entity = node_load($entity->field_associated_newsroom_select['und'][0]['target_id']);
    }

    return $entity;
  }

  /**
   * Generates the summary block.
   *
   * @return string
   *   The content of the block.
   */
  public function generateContent() {

    $this->getFilters();
    $events_terms = NewsroomHelper::getEventsTermsIds();
    $blocks = array();
    foreach ($this->getTypes() as $key => $type) {
      if (in_array($type->tid, $events_terms)) {
        continue;
      }

      $blocks[] = new NewsroomBlock($type, $this->getTopics(), $this->getOperator());
    }

    $blocks[] = new NewsroomBlockAgenda(NULL, $this->getTopics(), $this->getOperator());

    usort($blocks, array('NewsroomSummaryBlock', 'sortBlocks'));
    return theme('newsroom_summary', array(
      'items' => $blocks,
      'rss' => $this->generateRss(),
    ));
  }

  /**
   * Sort newsroom boxes.
   */
  public function sortBlocks($a, $b) {
    $display_highlights_begin = variable_get('newsroom_display_highlights_begin', 0);
    $agenda_after_highlights = variable_get('newsroom_agenda_after_highlights', 0);
    $order_by_last_update = variable_get('newsroom_order_by_last_update', 0);
    if ($a->getHighlighted() < $b->getHighlighted()) {
      return $display_highlights_begin ? 1 : -1;
    }
    elseif ($a->getHighlighted() > $b->getHighlighted()) {
      return $display_highlights_begin ? -1 : 1;
    }
    elseif ($a->getIsAgenda() < $b->getIsAgenda()) {
      return $agenda_after_highlights ? 1 : -1;
    }
    elseif ($a->getIsAgenda() > $b->getIsAgenda()) {
      return $agenda_after_highlights ? -1 : 1;
    }
    elseif ($a->getLatestDate() < $b->getLatestDate()) {
      return $order_by_last_update ? 1 : -1;
    }
    elseif ($a->getLatestDate() > $b->getLatestDate()) {
      return $order_by_last_update ? -1 : 1;
    }
    else {
      return 0;
    }
  }

}
