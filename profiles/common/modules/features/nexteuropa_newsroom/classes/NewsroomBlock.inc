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

  /**
   * Getter.
   */
  public function getItems() {
    return $this->items;
  }

  /**
   * Setter.
   */
  public function setItems($value) {
    $this->items = $value;
  }

  /**
   * Contructor of NewsroomBlock class.
   *
   * @param object $type
   *   Newsroom type taxonomy term.
   * @param array|object $topics
   *   Newsroom topics taxonomy terms.
   * @param string $operator
   *   Operator connecting  topics.
   */
  public function __construct($type, $topics, $operator) {
    parent::__construct($type, $topics, $operator);
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

  /**
   * Gets block data from db.
   */
  public function getData() {
    $topic_ids = $this->getTopicsId();
    $cache_key = 'newsroom:summary_block:' . md5($this->getType()->tid . implode('', $topic_ids));
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $result = $cache->data;
    }
    else {
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
        if ($this->getOperator() == 'OR') {
          $query->condition('topic_data.tid', $topic_ids);
        }
        else {
          $nids = NewsroomHelper::getNodeRelatedToTopic($this->getTopicsId());
          if ($nids) {
            $query->condition('nid', $nids, 'IN');
          }
        }
      }

      $type = $this->getType();
      $query->condition('tt.tid', NewsroomHelper::getTermChildren($type->tid));
      $query->range(0, NewsroomHelper::getBlockItemsNumber($this->getHighlighted()));
      $query->orderBy('n.created', 'DESC');
      $result = $query->execute()->fetchAll();

      cache_set($cache_key, $result, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }

    if ($result) {
      $this->setLatestDate($result[0]->created);
    }

    foreach ($result as $key => $item) {
      $result[$key]->new = NewsroomHelper::isNewItem($item->created, $item->nid);
    }

    $this->setItems($result);
  }

  /**
   * Generates block content.
   */
  public function generateContent() {
    return theme('newsroom_summary_block', array(
      'content' => $this->getContent(),
      'css_classes' => $this->getCssClasses(),
      'title' => $this->getTitle(),
      'type_url' => $this->getTypeUrl(),
      'url' => NewsroomHelper::getNewsroomUrl($this->getTypeUrl(), $this->getTopicUrl()),
    ));
  }

  /**
   * Generates block items content.
   */
  protected function getContent() {
    return theme('newsroom_summary_block_item', array(
      'items' => $this->getItems(),
    ));
  }

}
