<?php

/**
 * @file
 * Code for the NewsroomAgenda class.
 */

/**
 * NewsroomAgenda class base class.
 */
abstract class NewsroomAgenda {

  const AGENDA_VIEW_SCHEDULE = 'schedule';
  const AGENDA_VIEW_MONTH = 'month';
  const AGENDA_VIEW_WEEK = 'week';
  const AGENDA_VIEW_DAY = 'day';
  const AGENDA_VIEW_SCHEDULE_BLOCK = 'schedule-block';

  protected $view = NewsroomAgenda::AGENDA_VIEW_SCHEDULE;
  protected $topicUrl = 'all';
  protected $topics = array();
  protected $typeUrl = 'all';
  protected $typeId = NULL;
  protected $currentDate = NULL;
  protected $nextDate = NULL;
  protected $previousDate = NULL;
  protected $currentItems = array();
  protected $nextItems = array();
  protected $result = array();
  protected $query = NULL;
  protected $itemsCount = 0;
  protected $urlParts = array();
  protected $displayCalendar = TRUE;
  protected $isBlock = FALSE;

  /**
   * Getter.
   */
  public function getDisplayCalendar() {
    return $this->displayCalendar;
  }

  /**
   * Get minimal items number per agenda page.
   *
   * @return int
   *   Number of items.
   */
  public function getItemsNumber() {
    return variable_get('newsroom_agenda_page_items_number', 10);
  }

  /**
   * Setter.
   */
  public function setDisplayCalendar($value) {
    $this->displayCalendar = $value;
  }

  /**
   * Getter.
   */
  public function getIsBlock() {
    return $this->isBlock;
  }

  /**
   * Setter.
   */
  public function setIsBlock($value) {
    $this->isBlock = $value;
  }

  /**
   * Getter.
   */
  public function getView() {
    return $this->view;
  }

  /**
   * Setter.
   */
  public function setView($value) {
    $this->view = $value;
  }

  /**
   * Getter.
   */
  public function getItemsCount() {
    return $this->itemsCount;
  }

  /**
   * Getter.
   */
  public function getUrlParts() {
    return $this->urlParts;
  }

  /**
   * Getter.
   */
  public function getTopicUrl() {
    return $this->topicUrl;
  }

  /**
   * Setter.
   */
  public function setTopicUrl($value) {
    $this->topicUrl = !empty($value) ? pathauto_cleanstring($value) : 'all';
  }

  /**
   * Getter.
   */
  public function getTypeUrl() {
    return $this->typeUrl;
  }

  /**
   * Setter.
   */
  public function setTypeUrl($value) {
    $this->typeUrl = !empty($value) ? pathauto_cleanstring($value) : 'all';
  }

  /**
   * Getter.
   */
  public function getCurrentItems() {
    return $this->currentItems;
  }

  /**
   * Setter.
   */
  public function setCurrentItems($value) {
    $this->currentItems = $this->sortItems($value);
  }

  /**
   * Getter.
   */
  public function getNextItems() {
    return $this->nextItems;
  }

  /**
   * Setter.
   */
  public function setNextItems($value) {
    $this->nextItems = $this->sortItems($value);
  }

  /**
   * Getter.
   */
  public function getNextDate() {
    return $this->nextDate;
  }

  /**
   * Setter.
   */
  public function setNextDate($value) {
    $this->nextDate = $value;
  }

  /**
   * Setter.
   */
  public function getPreviousDate() {
    return $this->previousDate;
  }

  /**
   * Getter.
   */
  public function setPreviousDate($value) {
    $this->previousDate = $value;
  }

  /**
   * Getter.
   */
  public function getCurrentDate() {
    return $this->currentDate;
  }

  /**
   * Setter.
   */
  public function setCurrentDate($value) {
    $value->setTime(0, 0, 0);
    $this->currentDate = $value;
  }

  /**
   * Getter.
   */
  public function getQuery() {
    return $this->query;
  }

  /**
   * Setter.
   */
  public function setQuery($value) {
    $this->query = $value;
  }

  /**
   * Getter.
   */
  public function getResult() {
    return $this->result;
  }

  /**
   * Setter.
   */
  public function setResult($value) {
    $this->result = $value;
  }

  /**
   * Setter.
   */
  public function setTypeId($value) {
    $this->typeId = $value;
  }

  /**
   * Getter.
   */
  public function getTypeId() {
    return $this->typeId;
  }

  /**
   * Setter.
   */
  public function setTopics($value) {
    $this->topics = $value;
  }

  /**
   * Getter.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Add item count.
   */
  public function addItemsCount() {
    $this->itemsCount++;
  }

  /**
   * Clear URL parts.
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
   * @param string $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topics.
   */
  public function __construct($type, $topics = array()) {
    if ($type) {
      $this->setTypeId($type->tid);
      $this->setTypeUrl($type->name);
    }

    if (is_object($topics)) {
      $this->setTopicUrl($topics->name);
      $topics = array($topics);
    }

    $this->setTopics($topics);

    $this->addUrlPart($this->getView());
    $this->addUrlPart($this->getTypeUrl());
    $this->addUrlPart($this->getTopicUrl());
  }

  /**
   * Prepare agenda components: query, result, the dates range.
   */
  protected function prepareAgenda() {
    $this->getBaseQuery();
    $this->setResult($this->prepareResult($this->loadResult()));
    $this->setupAgenda();
  }

  /**
   * Returns previous title.
   *
   * @return string
   *   Title
   */
  public function getPreviousTitle() {
    return t('Previous');
  }

  /**
   * Returns next title.
   *
   * @return string
   *   Title
   */
  public function getNextTitle() {
    return t('Next');
  }

  /**
   * Returns form id with the current ID.
   *
   * @param string $form_id
   *   Form ID.
   *
   * @return array
   *   Form array.
   */
  protected function getForm($form_id) {
    $topics = $this->getTopics();
    $topic_id = count($topics) == 1 ? $topics[0]->tid : NULL;
    $result_topics = $form_id == 'nexteuropa_newsroom_agenda_filter_form' ? $this->getResultTopicsId() : NULL;
    return drupal_get_form($form_id, $this->getView(), $this->getTypeId(), $topic_id, $this->getCurrentDate()->format('Y-m-d'), $result_topics);
  }

  /**
   * Returns the agenda html.
   *
   * @return string
   *   HTML.
   */
  public function getAgenda() {
    $cache_key = 'get_agenda:page:' . $this->getUniqueCachePart();
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $content = $cache->data;
    }
    else {
      $this->prepareAgenda();
      $content = theme('newsroom_agenda_page', array(
        'filter_form' => $this->getForm('nexteuropa_newsroom_agenda_filter_form'),
        'date_form' => $this->getDisplayCalendar() ? $this->getForm('nexteuropa_newsroom_agenda_datepicker_form') : NULL,
        'items' => $this->getCurrentItems(),
        'next_event_items' => $this->getNextItems(),
        'is_block' => $this->getIsBlock(),
        'navigation' => array(
          'previous' => $this->getPreviousDate() ? $this->getNavigationLink($this->getPreviousTitle(), $this->getPreviousDate()) : NULL,
          'next' => $this->getNextDate() ? $this->getNavigationLink($this->getNextTitle(), $this->getNextDate()) : NULL,
        ),
      ));
      cache_set($cache_key, $content, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }

    return $content;
  }

  /**
   * Generate content for Agenda block.
   *
   * @return string
   *   Content of the block.
   */
  public function getBlockAgenda() {
    $cache_key = 'get_agenda:block:' . $this->getUniqueCachePart();
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $content = $cache->data;
    }
    else {
      $this->prepareAgenda();
      $content = theme('newsroom_agenda_page', array(
        'filter_form' => NULL,
        'date_form' => NULL,
        'items' => $this->getCurrentItems(),
        'is_block' => $this->getIsBlock(),
        'next_event_items' => $this->getNextItems(),
        'navigation' => array(),
      ));
      cache_set($cache_key, $content, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $content;
  }

  /**
   * Gets the unique part for cache value.
   *
   * @return string
   *   Cache key unique value.
   */
  protected function getUniqueCachePart() {
    return md5($this->getCurrentDate()->format('Y-m-d') . $this->getTypeId() . implode('', $this->getTopicsId()));
  }

  /**
   * Returns the base query for agenda presentation.
   */
  public function getBaseQuery() {
    $query = db_select('node', 'n');
    $query->distinct();
    $query->fields('n', array('nid', 'title', 'created'));
    $query->fields('tt', array('name'));
    $query->addField('tt', 'tid', 'type_id');
    $query->addField('d', 'field_newsroom_item_date_value', 'start_date');
    $query->addField('d', 'field_newsroom_item_date_value2', 'end_date');
    $query->join('field_data_field_newsroom_item_date', 'd', 'd.entity_id = n.nid');
    $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
    $query->join('taxonomy_term_data', 'tt', 'tt.tid = tf.field_newsroom_item_type_tid');
    $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
    $query->leftJoin('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
    $query->condition('n.status', 1);
    $query->condition('tf.field_newsroom_item_type_tid', NewsroomHelper::getEventsTermsIds());
    $query->orderBy('d.field_newsroom_item_date_value');
    $query->orderBy('d.field_newsroom_item_date_value2');

    if ($this->getTypeId()) {
      $query->condition('tt.tid', NewsroomHelper::getTermChildren($this->getTypeId()));
    }

    $this->setQuery($this->processQuery($query));
  }

  /**
   * TBC.
   */
  protected function processQuery($query) {
    if (count($this->getTopics()) > 0) {
      $query->condition('topic_data.tid', $this->getTopicsId());
    }
    return $query;
  }

  /**
   * Build the agenda array based on the end and start date.
   *
   * @param DateTime $start_input_date
   *   Start date.
   * @param DateTime $end_input_date
   *   End date.
   * @param bool $build_empty_days
   *   Add empty days or not.
   *
   * @return array
   *   Agenda items events.
   */
  public function buildAgenda(DateTime $start_input_date, DateTime $end_input_date, $build_empty_days = TRUE) {
    $start_date = clone $start_input_date;
    $end_date = clone $end_input_date;
    $output = array();
    $items = $this->getResult();

    while ($start_date < $end_date) {
      $agenda_item = new NewsroomAgendaItem();
      $agenda_item->setDate(clone $start_date);

      foreach ($items as $item) {
        if ($item->start_date_obj <= $start_date && $item->end_date_obj >= $start_date) {
          $this->addItemsCount();
          $agenda_item->addItem($item);
        }
      }

      if ($build_empty_days || (!$build_empty_days && (count($agenda_item->getItems()) > 0))) {
        $output[] = $agenda_item;
      }

      $start_date->modify('+1 day');
    }

    return $output;
  }

  /**
   * Convert string to date object and fill empty dates.
   *
   * @param array $items
   *   Agenda items.
   *
   * @return array
   *   Prepared agenda items.
   */
  protected function prepareResult($items) {
    if (!empty($items) && count($items) > 0) {
      foreach ($items as $key => $item) {
        $items[$key]->new = NewsroomHelper::isNewItem($item->created, $item->nid);
        if (empty($item->start_date_obj)) {
          $dt_object = new DateTime();
          if (!empty($item->start_date)) {
            $dt_object->setTimestamp($item->start_date);
          }
          $dt_object->setTime(0, 0, 0);
          $items[$key]->start_date_obj = $dt_object;
        }
        // If the end date is empty, it means it is one day event and we set the
        // end date to start date.
        if (empty($item->end_date_obj)) {
          $dt_object = new DateTime();
          $dt_object->setTimestamp(!empty($item->end_date) ? $item->end_date : $item->start_date);
          $dt_object->setTime(0, 0, 0);
          $items[$key]->end_date_obj = $dt_object;
        }
      }
    }
    return $items;
  }

  /**
   * Returns navigation link based on URL.
   *
   * @param string $title
   *   Link title.
   * @param DateTime $date
   *   Datetime object.
   *
   * @return string
   *   HTML link.
   */
  protected function getNavigationLink($title, DateTime $date) {
    return $date ? l($title, $this->getNavigationUrl($date)) : NULL;
  }

  /**
   * Returns agenda navigation URL.
   *
   * @param DateTime $date
   *   Datetime object.
   *
   * @return string
   *   URL string.
   */
  public function getNavigationUrl(DateTime $date) {
    $this->clearUrlParts();
    $this->addUrlPart($this->getView());
    $this->addUrlPart($this->getTypeUrl());
    $this->addUrlPart($this->getTopicUrl());
    $this->setUrlItems($date);
    return 'newsroom-agenda/' . implode('/', $this->getUrlParts());
  }

  /**
   * Setups agenda conditions.
   */
  protected function setupAgenda() {
    $this->setCurrentItems($this->buildAgenda($this->getCurrentDate(), $this->getNextDate()));
  }

  /**
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    $end_date_condition = db_and()
      ->condition('d.field_newsroom_item_date_value2', $this->getCurrentDate()->format('Y-m-d'), '>=')
      ->condition('d.field_newsroom_item_date_value', $this->getNextDate()->format('Y-m-d'), '<=');

    $start_date_condition = db_and()
      ->condition('d.field_newsroom_item_date_value', $this->getCurrentDate()->format('Y-m-d'), '>=')
      ->condition('d.field_newsroom_item_date_value', $this->getNextDate()->format('Y-m-d'), '<=')
      ->isNull('d.field_newsroom_item_date_value2');

    $date_condition = db_or();
    $date_condition->condition($end_date_condition);
    $date_condition->condition($start_date_condition);

    $this->getQuery()->condition($date_condition);
    return $this->getQuery()->execute()->fetchAll();
  }

  /**
   * Sort agenda items.
   */
  protected function sortItems($items) {
    foreach ($items as $key => $item) {
      $events = $item->getItems();
      usort($events, function ($a, $b) {
        $a_start_date_obj = $a->start_date_obj;
        $b_start_date_obj = $b->start_date_obj;
        $a_end_date_obj = $a->end_date_obj;
        $b_end_date_obj = $b->end_date_obj;

        if ($a_end_date_obj < $b_end_date_obj) {
          return -1;
        }
        elseif ($a_end_date_obj > $b_end_date_obj) {
          return 1;
        }
        else {
          if ($a_end_date_obj == $b_end_date_obj) {
            return 0;
          }
          else {
            return $a_start_date_obj > $b_start_date_obj ? -1 : 1;
          }
        }
      });
      $item->setItems($events);
      $items[$key] = $item;
    }

    return $items;
  }

  /**
   * Get IDs array from topics array.
   *
   * @return array
   *   Array of IDs.
   */
  protected function getTopicsId() {
    $topic_ids = array();
    if (count($this->getTopics()) > 0) {
      foreach ($this->getTopics() as $topic) {
        $topic_ids[] = $topic->tid;
      }
    }
    return $topic_ids;
  }

  /**
   * Get IDs array from topics array.
   *
   * @return array
   *   Array of IDs.
   */
  protected function getResultTopicsId() {
    $cache_key = 'result_topics';
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $tids = $cache->data;
    }
    else {
      $query = db_select('node', 'n');
      $query->distinct();
      $query->fields('topic_data', array('tid'));
      $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
      $query->join('taxonomy_term_data', 'tt', 'tt.tid = tf.field_newsroom_item_type_tid');
      $query->join('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
      $query->join('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
      $query->condition('n.status', 1);
      $query->condition('tf.field_newsroom_item_type_tid', NewsroomHelper::getEventsTermsIds());
      $tids = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $tids, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $tids;
  }

  /**
   * Adds date url parts.
   */
  abstract protected function setUrlItems(DateTime $date);

}
