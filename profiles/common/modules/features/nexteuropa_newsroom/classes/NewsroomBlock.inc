<?php

/**
 * @file
 * Code for the NewsroomBlock class.
 */

/**
 * NewsroomBlock class base class.
 */
class NewsroomBlock extends NewsroomBlockBase {
  protected $items = array();
  
  public function getItems() {
    return $this->items;
  }
  
  public function setItems($value) {
    $this->items = $value;
  }

  /**
   * 
   * @param type $type
   * @param type $topics
   */
  public function __construct($type, $topics) {
    parent::__construct($type, $topics);
    $this->setIsAgenda(FALSE);
    $this->setHighlighted();
    $this->getData();
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
    return pathauto_cleanstring(NewsroomHelper::getTermTranslatedName($this->getType()));
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
    $this->highlighted = isset($this->getType()->field_newsroom_highlighted[LANGUAGE_NONE][0]['value']) ? $this->getType()->field_newsroom_highlighted[LANGUAGE_NONE][0]['value'] : 0;
  }

  public function getItemsNumber() {
    $front_page = drupal_is_front_page();
    if ($this->getHighlighted()) {
      // Highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_highlighted_items' : 'newsroom_summary_block_num_highlighted_items';
    }
    else {
      // Not highlighted type, home | not home.
      $variable_name = $front_page ? 'newsroom_summary_home_block_num_items' : 'newsroom_summary_block_num_items';
    }

    return variable_get($variable_name, 5);
  }

  public function getData() {
    $topic_ids = $this->getTopicsId();
    
    $result = NULL;
//    $cache_key = 'newsroom:summary_block:' . md5($this->getType()->tid . implode('', $topic_ids));
//    $cache = cache_get($cache_key, NEWSROOM_CACHE_TABLE);
//    if ($cache) {
//      $result = $cache->data;
//    } else {
      $query = db_select('node', 'n');
      $query->distinct();
      $query->fields('n', array('nid', 'title', 'created'));
      $query->fields('tt', array('name'));
      $query->addField('tt', 'tid', 'type_id');
      $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
      $query->join('taxonomy_term_data', 'tt', 'tt.tid = tf.field_newsroom_item_type_tid');
      $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
      $query->leftJoin('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
      $query->condition('n.status', 1);

      if (count($topic_ids) > 0) {
        $query->condition('topic_data.tid', $topic_ids);
      }

      $type = $this->getType();
      $query->condition('tt.tid', NewsroomHelper::getTermChildren($type->tid));
      $query->range(0, $this->getItemsNumber());
      $query->orderBy('n.created', 'DESC');
      $result = $query->execute()->fetchAll();

      
//
//      cache_set($cache_key, $result, NEWSROOM_CACHE_TABLE, time() + 3600);
//    }
    
    if ($result) {
      $this->setLatestDate($result[0]->created);
    }
    
    foreach ($result as $key => $item) {
      $result[$key]->new = NewsroomHelper::isNewItem($item->created, $item->nid);
    }

    $this->setItems($result);
  }

  public function generateContent() {
    return theme('newsroom_summary_block', array(
      'content' => $this->getContent(),
      'css_classes' => $this->getCssClasses(),
      'title' => $this->getTitle(),
      'type_url' => $this->getTypeUrl(),
      'url' => NewsroomHelper::getNewsroomUrl($this->getTypeUrl(), $this->getTopicUrl()),
    ));
  }
  
  protected function getContent() {
    return theme('newsroom_summary_block_item', array(
      'items' => $this->getItems(),
    ));
  }
}
