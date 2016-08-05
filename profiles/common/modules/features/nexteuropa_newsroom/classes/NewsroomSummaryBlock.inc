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
  protected $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;

  /**
   * Gets newsroom topics.
   *
   * @return array
   *   Newsroom topics.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Sets newsroom topics.
   *
   * @param array $value
   *   Newsroom topics.
   */
  public function setTopics($value) {
    $this->topics = $value;
  }

  /**
   * Sets newsroom types.
   *
   * @param array $value
   *   Newsroom types.
   */
  public function setTypes($value) {
    $this->types = $value;
  }

  /**
   * Gets newsroom types.
   *
   * @return array
   *   Newsroom types
   */
  public function getTypes() {
    return $this->types;
  }

  /**
   * Gets query operator.
   *
   * @return string
   *   Query operator: OR or AND.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Sets query operator.
   *
   * @param string $value
   *   Query operator: OR or AND.
   */
  public function setOperator($value) {
    $this->operator = $value;
  }

  /**
   * Generates RSS link based on topics.
   *
   * @return string
   *   RSS link.
   */
  protected function generateRss() {
    $topics = $this->getTopics();
    $topic_url = NULL;
    $topic_name = NULL;

    // We take only first topic if we have multiple.
    if (count($topics) > 0) {
      $topic_name = $topics[0]->name;
      $topic_url = pathauto_cleanstring($topics[0]->name);
    }
    else {
      $url_parts[] = NEXTEUROPA_NEWSROOM_ALL;
    }

    $rss_path = NewsroomHelper::getNewsroomRssUrl(array(NEXTEUROPA_NEWSROOM_ALL, $topic_url));
    $rss_title = !empty($topic_name) ? 'RSS feed : ' . $topic_name : 'RSS feed';

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

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $config = $cache->data;
    }
    else {
      $topic_operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;
      $selected_topics = array();
      $selected_types = array();

      $entity = $this->getEntityFromRequest();
      if ($entity) {
        if (isset($entity->type) && $entity->type == 'newsroom_selection') {

          if (NewsroomHelper::getFieldValue($entity, 'field_newsroom_topic_operator')) {
            $topic_operator = NewsroomHelper::getFieldValue($entity, 'field_newsroom_topic_operator');
          }

          // Get topics from newsroom selection.
          if ($topic_config = field_get_items('node', $entity, 'field_newsroom_selected_topics')) {
            foreach ($topic_config as $term_ref) {
              $selected_topics[] = $term_ref['target_id'];
            }
          }

          // Get types from newsroom selection.
          $type_config = field_get_items('node', $entity, 'field_newsroom_selected_types');
          if ($type_config) {
            foreach ($type_config as $term_ref) {
              $selected_types[] = $term_ref['tid'];
            }
          }
        }
        elseif (NewsroomHelper::getFieldValue($entity, 'field_newsroom_associated_topic', 'tid')) {
          // If it has the associated field, try to load topic.
          $selected_topics = array(
            NewsroomHelper::getFieldValue($entity, 'field_newsroom_associated_topic', 'tid'),
          );
        }
      }

      $types = array();
      if (count($selected_types) > 0) {
        foreach ($selected_types as $type_id) {
          $types[] = NewsroomHelper::getNewsroomType($type_id);
        }
      }
      else {
        $types = NewsroomHelper::getNewsroomTypes();
        // We need only the first level of types.
        foreach ($types as $key => $type) {
          if ($type->depth > 0) {
            unset($types[$key]);
          }
        }
      }

      $topics = array();
      foreach ($selected_topics as $topic_id) {
        $topics[] = NewsroomHelper::getNewsroomTopic($topic_id);
      }

      $config['topic'] = $topics;
      $config['topic_operator'] = $topic_operator;
      $config['type'] = $types;

      cache_set($cache_key, $config, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_summary_filter', 3600));
    }

    $this->setTopics($config['topic']);
    $this->setTypes($config['type']);
    $this->setOperator($config['topic_operator']);
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
    if ($newsroom_selection_id = NewsroomHelper::getFieldValue($entity, 'field_newsroom_associated_select', 'target_id')) {
      // If it has the selection field, try to load config.
      $entity = node_load($newsroom_selection_id);
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
    $output = NULL;

    foreach ($this->getTypes() as $key => $type) {
      if (in_array($type->tid, $events_terms)) {
        continue;
      }

      $blocks[] = new NewsroomBlock($type, $this->getTopics(), $this->getOperator());
    }

    $blocks[] = new NewsroomBlockAgenda(NULL, $this->getTopics(), $this->getOperator());

    usort($blocks, array('NewsroomSummaryBlock', 'sortBlocks'));
    foreach ($blocks as $block) {
      $output .= $block->generateContent();
    }
    return theme('newsroom_summary_block', array(
      'content' => $output,
      'rss' => $this->generateRss(),
    ));
  }

  /**
   * Callback: sorts newsroom boxes.
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
