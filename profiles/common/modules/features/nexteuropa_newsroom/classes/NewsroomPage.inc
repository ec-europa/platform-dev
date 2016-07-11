<?php
/**
 * @file
 * Code for the NewsroomPage class.
 */

/**
 * NewsroomPage class.
 */
class NewsroomPage {

  const DATE_FORMAT = 'd/m/Y';

  protected $topicUrl = 'all';
  protected $typeUrl = 'all';
  protected $typeId = NULL;
  protected $topicId = NULL;
  protected $result = array();
  protected $urlParts = array();

  /**
   * Gets minimal items number per agenda page.
   *
   * @return int
   *   Number of items.
   */
  public function getItemsNumber() {
    return variable_get('newsroom_agenda_page_items_number', 10);
  }

  /**
   * Gets url parts.
   *
   * @return array
   *   URL parts.
   */
  public function getUrlParts() {
    return $this->urlParts;
  }

  /**
   * Gets topic url.
   *
   * @return string
   *   Topic URL part.
   */
  public function getTopicUrl() {
    return $this->topicUrl;
  }

  /**
   * Sets topic URL.
   *
   * @param string $value
   *   Topic URL part.
   */
  public function setTopicUrl($value) {
    $this->topicUrl = !empty($value) ? pathauto_cleanstring($value) : 'all';
  }

  /**
   * Gets type URL.
   *
   * @return string
   *   Type URL part.
   */
  public function getTypeUrl() {
    return $this->typeUrl;
  }

  /**
   * Sets type URL.
   *
   * @param string $value
   *   Type URL part.
   */
  public function setTypeUrl($value) {
    $this->typeUrl = !empty($value) ? pathauto_cleanstring($value) : 'all';
  }

  /**
   * Gets results.
   *
   * @return array
   *   DB data result.
   */
  public function getResult() {
    return $this->result;
  }

  /**
   * Gets data from DB.
   */
  public function getData() {
//    $cache_key = 'page_result:' . md5($this->getUniqueCachePart());
//    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
//    if ($cache) {
//      $data = $cache->data;
//    }
//    else {
      $data = $this->fetchData();
//      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_page_result', 300));
//    }

    return $data;
  }

  /**
   * Sets type id.
   *
   * @param int $value
   *   Type id.
   */
  public function setTypeId($value) {
    $this->typeId = $value;
  }

  /**
   * Gets type id.
   *
   * @return int
   *   Type id.
   */
  public function getTypeId() {
    return $this->typeId;
  }

  /**
   * Sets start date.
   *
   * @param string $value
   *   Start date.
   */
  public function setStartDate($value) {
    $this->start_date = $value;
  }

  /**
   * Gets start date.
   *
   * @return string
   *   Start date.
   */
  public function getStartDate() {
    return $this->start_date;
  }

  /**
   * Sets end date.
   *
   * @param string $value
   *   End date.
   */
  public function setEndDate($value) {
    $this->end_date = $value;
  }

  /**
   * Gets end date.
   *
   * @return string
   *   End date.
   */
  public function getEndDate() {
    return $this->end_date;
  }

  /**
   * Sets topic id.
   *
   * @param int $value
   *   Topic id.
   */
  public function setTopicId($value) {
    $this->topicId = $value;
  }

  /**
   * Gets topic id.
   *
   * @return int
   *   Topic id.
   */
  public function getTopicId() {
    return $this->topicId;
  }

  /**
   * Clears URL parts.
   */
  public function clearUrlParts() {
    $this->urlParts = array();
  }

  /**
   * Adds URL part.
   *
   * @param string $value
   *   URL part.
   */
  public function addUrlPart($value) {
    $this->urlParts[] = $value;
  }

  /**
   * NewsroomAgenda constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param object $topic
   *   Newsroom topic.
   * @param string $start_date
   *   Start date.
   * @param string $end_date
   *   End date.
   */
  public function __construct($type = NULL, $topic = NULL, $start_date = NULL, $end_date = NULL) {
    if ($type) {
      $this->setTypeId($type->tid);
      $this->setTypeUrl($type->name);
    }

    if ($topic) {
      $this->setTopicId($topic->tid);
      $this->setTopicUrl($topic->name);
    }

    $this->addUrlPart($this->getTypeUrl());
    $this->addUrlPart($this->getTopicUrl());
    $this->setStartDate($start_date);
    $this->setEndDate($end_date);

    if ($start_date) {
      $this->addUrlPart($start_date);
    }
    
    if ($end_date) {
      $this->addUrlPart($end_date);
    }

  }

  /**
   * Returns the newsroom page html.
   *
   * @return string
   *   HTML.
   */
  public function getContent() {
    $filter_form = drupal_get_form('nexteuropa_newsroom_newsroom_page_filter_form', $this->getTypeId(), $this->getTopicId(), $this->getStartDate(), $this->getEndDate());
    $content = theme('newsroom_page', array(
      'filter_form' => drupal_render($filter_form),
      'items' => $this->prepareItemsOutput($this->getData()),
    ));    
    return $content;
  }

  /**
   * Prepares page items for presenation.
   *
   * @param array $items
   *   Agenda items.
   *
   * @return string
   *   Output string.
   */
  protected function prepareItemsOutput($items) {
    $output = '';
    foreach ($items as $item) {
      $image = NULL;
      if ($item->fid) {
        $file = file_load($item->fid);
        if ($file) {
          $image = theme('image_style', array('path' => $file->uri, 'alt' => t($file->title), 'style_name' => 'newsroom_style'));
        }
      }
      $start_date_obj = NULL;
      $end_date_obj = NULL;
      if (!empty($item->start_date)) {
        $start_date_obj = new DateTime();
        $start_date_obj->setTimestamp($item->start_date);
      }
      if (!empty($item->end_date)) {
        $end_date_obj = new DateTime();
        $end_date_obj->setTimestamp($item->end_date);
      }
      $output .= theme('newsroom_page_item', array(
        'start_date' => $start_date_obj ? $start_date_obj->format(NewsroomPage::DATE_FORMAT) : NULL,
        'end_date' => $end_date_obj ? $end_date_obj->format(NewsroomPage::DATE_FORMAT) : NULL,
        'title' => empty($item->short_title) ? $item->title : $item->short_title,
        'teaser' => $item->teaser,
        'type_url' => NewsroomHelper::getNewsroomPageUrl(pathauto_cleanstring($item->type_title), 'all'),
        'type_title' => $item->type_title,
        'node_url' => empty($item->main_link) ? 'node/' . $item->nid : $item->main_link,
        'image' => $image,
        'venue' => $item->venue,
      ));
    }
    return $output;
  }

  /**
   * Gets the unique part for cache value.
   *
   * @return string
   *   Cache key unique value.
   */
  protected function getUniqueCachePart() {
    return $this->getTypeId() . $this->getTopicId();
  }

  /**
   * Fetchs the data from DB.
   */
  public function fetchData() {
    $query = db_select('node', 'n');
    $query->distinct();
    $query->fields('n', array('nid', 'title', 'created'));
    $query->addField('type_data', 'name', 'type_title');
    $query->addField('d', 'field_newsroom_item_date_value', 'start_date');
    $query->addField('d', 'field_newsroom_item_date_value2', 'end_date');
    $query->addField('teaser', 'field_newsroom_teaser_value', 'teaser');
    $query->addField('image', 'field_newsroom_illustrative_img_fid', 'fid');
    $query->addField('venue_data', 'field_newsroom_item_venue_value', 'venue');
    $query->addField('main_link_data', 'field_newsroom_item_main_link_url', 'main_link');
    $query->addField('short_title_data', 'field_short_title_value', 'short_title');
    
    $query->leftJoin('field_data_field_newsroom_teaser', 'teaser', 'teaser.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_illustrative_img', 'image', 'image.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_item_date', 'd', 'd.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_item_type', 'type_field', 'type_field.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_item_venue', 'venue_data', 'venue_data.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_item_main_link', 'main_link_data', 'main_link_data.entity_id = n.nid');
    $query->leftJoin('field_data_field_short_title', 'short_title_data', 'short_title_data.entity_id = n.nid');
    
    $query->leftJoin('taxonomy_term_data', 'type_data', 'type_data.tid = type_field.field_newsroom_item_type_tid');
    $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
    $query->leftJoin('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
    
    $query->condition('n.status', 1);
    $query->condition('n.type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    $query->orderBy('d.field_newsroom_item_date_value', 'DESC');
    $query->orderBy('d.field_newsroom_item_date_value2', 'DESC');

    if (NewsroomHelper::getEventsTermsIds()) {
      
    }

    if ($this->getTypeId()) {
      $query->condition('type_data.tid', $this->getTypeId());
    }

    if ($this->getTopicId()) {
      $query->condition('topic_data.tid', $this->getTopicId());
    }

    return $query->extend('PagerDefault')->limit($this->getItemsNumber())->execute()->fetchAll();
  }

  /**
   * Returns navigation link based on URL.
   *
   * @return string|null
   *   HTML link.
   */
  public function getNavigationUrl() {
    $this->clearUrlParts();
    $this->addUrlPart($this->getTypeUrl());
    $this->addUrlPart($this->getTopicUrl());

    return url('newsroom-page/' . implode('/', $this->getUrlParts()));
  }

}
