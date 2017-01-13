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
   * Gets block items.
   *
   * @return array
   *   Block items.
   */
  public function getItems() {
    return $this->items;
  }

  /**
   * Sets block items.
   *
   * @param array $value
   *   Block items.
   */
  public function setItems($value) {
    $this->items = $value;
  }

  /**
   * Gets block title.
   *
   * @return string
   *   Title.
   */
  public function getTitle() {
    return $this->getType()->name;
  }

  /**
   * Gets type URL.
   *
   * @return string
   *   Type URL.
   */
  public function getTypeUrl() {
    return pathauto_cleanstring($this->getType()->name);
  }

  /**
   * Gets topic URL.
   *
   * @return string
   *   Topic URL.
   */
  public function getTopicUrl() {
    $url = NEXTEUROPA_NEWSROOM_ALL;
    $topics = $this->getTopics();
    if (count($topics) == 1) {
      $topic = reset($topics);
      $url = pathauto_cleanstring($topic->name);
    }

    return $url;
  }

  /**
   * Sets is block highlighted.
   */
  public function setHighlighted() {
    $this->highlighted = NewsroomHelper::getFieldValue($this->getType(), 'field_newsroom_highlighted');
  }

  /**
   * Gets block data from db.
   */
  public function getData() {
    $topic_ids = $this->getTopicsId();
    $cache_key = 'newsroom:summary_block:' . md5($this->getType()->tid . implode('', $topic_ids));

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
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
      $query->condition('n.type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);

      if (count($topic_ids) > 0) {
        if ($this->getOperator() == NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
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
      $query->condition('tt.tid', NewsroomHelper::getTypeChildren($type->tid));
      $query->range(0, NewsroomHelper::getBlockItemsNumber($this->getHighlighted()));
      $query->orderBy('n.created', 'DESC');
      $result = $query->execute()->fetchAll();

      cache_set($cache_key, $result, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_summary_block', 3600));
    }

    if ($result) {
      $this->setLatestDate($result[0]->created);
    }

    foreach ($result as $key => $item) {
      $result[$key]->new = NewsroomHelper::isNewItem($item->created, $item->nid);
      $result[$key]->created = NewsroomHelper::getFormatedDate('d/m/Y', $item->created);
    }

    $this->setItems($result);
  }

  /**
   * Generates block content.
   *
   * @return string
   *   Block content.
   */
  public function generateContent() {
    return theme('newsroom_summary_block_wrapper', array(
      'content' => $this->getContent(),
      'css_classes' => $this->getCssClasses(),
      'title' => $this->getTitle(),
      'type_url' => $this->getTypeUrl(),
      'url' => NewsroomHelper::getNewsroomPageUrl(array($this->getTypeUrl(), $this->getTopicUrl())),
    ));
  }

  /**
   * Generates block items content.
   *
   * @return string
   *   Block items content.
   */
  protected function getContent() {
    return theme('newsroom_summary_block_item', array(
      'items' => $this->getItems(),
    ));
  }

}
