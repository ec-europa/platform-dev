<?php

/**
 * @file
 * Code for the NewsroomBlock class.
 */

/**
 * NewsroomBlock class base class.
 */
class NewsroomBlock extends NewsroomBlockBase {

  /**
   * 
   * @param type $type
   * @param type $topics
   */
  public function __construct($type, $topics) {
    $this->setIsAgenda(FALSE);
    parent::__construct($type, $topics);
  }

  /**
   * Getter.
   */
  public function getTitle() {
    return NewsroomHelper::getTermTranslatedName($this->getType());
  }

  /**
   * Setter.
   */
  public function getTypeUrl() {
    return pathauto_cleanstring($this->getTitle());
  }

  /**
   * Setter.
   */
  public function getTopicUrl() {
    $url = 'all';
    $topics = $this->getTopics();
    if (count($topics) == 1) {
      $topic = reset($topics);
      $url = pathauto_cleanstring(NewsroomHelper::getTermTranslatedName($topic));
    }

    return $url;
  }
  
  /**
   * Setter.
   */
  public function setHighlighted() {
    return $this->highlighted = isset($this->getType()->field_newsroom_highlighted[LANGUAGE_NONE][0]['value']) ? $this->getType()->field_newsroom_highlighted[LANGUAGE_NONE][0]['value'] : 0;
  }

  public function getItemsNumber() {
    $front_page = drupal_is_front_page();
    if ($this->getHighlighted()) {
      // Highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_highlighted_items' : 'newsroom_summary_block_num_highlighted_items';
    } else {
      // Not highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_items' : 'newsroom_summary_block_num_items';
    }

    return variable_get($variable_name, 3);
  }

  public function getData() {
    $query = db_select('node', 'n');
    $query->distinct();
    $query->fields('n', array('nid', 'title'));
    $query->fields('tt', array('name'));
    $query->addField('tt', 'tid', 'type_id');
    $query->addField('d', 'field_newsroom_item_date_value', 'date');
    $query->join('field_data_field_newsroom_item_date', 'd', 'd.entity_id = n.nid');
    $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
    $query->join('taxonomy_term_data', 'tt', 'tt.tid = tf.field_newsroom_item_type_tid');
    $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
    $query->leftJoin('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
    $query->condition('n.status', 1);
    $query->orderBy('d.field_newsroom_item_date_value');
    $query->orderBy('d.field_newsroom_item_date_value2');

    $topic_ids = array();
    foreach ($this->getTopics() as $topic) {
      $topic_ids[] = $topic->tid;
    }

    if (count($topic_ids) > $topic_ids) {
      $query->condition('topic_data.tid', $topic_ids);
    }

    $type = $this->getType();
    $query->condition('tt.tid', NewsroomHelper::getTermChildren($type->tid));
    $query->range(0, $this->getItemsNumber());
    $query->orderBy('d.field_newsroom_item_date_value', 'DESC');
    
    $result = $query->execute()->fetchAll();
    if ($result) {
      foreach($result as $item) {
        $this->setLatestDate($item['date']);
      }
    }
    return $result;
  }

  public function generateContent() {
    $path = md5(current_path());
    $cache_key = 'newsroom:summary_block:' . $path;
    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $content = $cache->data;
    } else {
      $content = theme('newsroom_summary_block_item', array(
        'items' => $this->getData(),
        'highlighted' => $this->getHighlighted(),
        'title' => $this->getTitle(),
        'type_url' => $this->getTypeUrl(),
        'url' => NewsroomHelper::getNewsroomUrl($this->getTypeUrl(), $this->getTopicUrl()),
      ));

      cache_set($cache_key, $content, NEWSROOM_CACHE_TABLE, time() + 3600);
    }

    return $content;
  }
}
