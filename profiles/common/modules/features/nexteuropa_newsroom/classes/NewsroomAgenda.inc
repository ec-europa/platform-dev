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
  const DATE_FORMAT = 'Y-m-d';

  protected $view = NewsroomAgenda::AGENDA_VIEW_SCHEDULE;
  protected $topicUrl = NEXTEUROPA_NEWSROOM_ALL;
  protected $topics = array();
  protected $typeUrl = NEXTEUROPA_NEWSROOM_ALL;
  protected $typeId = NULL;
  protected $currentDate = NULL;
  protected $upcomingDate = NULL;
  protected $previousDate = NULL;
  protected $currentItems = array();
  protected $upcomingItems = array();
  protected $result = array();
  protected $query = NULL;
  protected $itemsCount = 0;
  protected $urlParts = array();
  protected $displayCalendar = TRUE;
  protected $isBlock = FALSE;

  /**
   * NewsroomAgenda constructor.
   *
   * @param object $type
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
  }

  /**
   * Gets display calendar value.
   *
   * @return bool
   *   Display or not the calendar.
   */
  public function getDisplayCalendar() {
    return $this->displayCalendar;
  }

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
   * Sets display calendar value.
   *
   * @param bool $value
   *   Display or not the calendar.
   */
  public function setDisplayCalendar($value) {
    $this->displayCalendar = $value;
  }

  /**
   * Gets is block.
   *
   * @return bool
   *   Is it a block or not.
   */
  public function getIsBlock() {
    return $this->isBlock;
  }

  /**
   * Sets is block.
   *
   * @param bool $value
   *   Is it a block or not.
   */
  public function setIsBlock($value) {
    $this->isBlock = $value;
  }

  /**
   * Gets view.
   *
   * @return string
   *   Type of view.
   */
  public function getView() {
    return $this->view;
  }

  /**
   * Sets view.
   *
   * @param string $value
   *   Type of view.
   */
  public function setView($value) {
    $this->view = $value;
  }

  /**
   * Gets items count.
   *
   * @return int
   *   Items count.
   */
  public function getItemsCount() {
    return $this->itemsCount;
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
    $this->topicUrl = !empty($value) ? pathauto_cleanstring($value) : NEXTEUROPA_NEWSROOM_ALL;
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
    $this->typeUrl = !empty($value) ? pathauto_cleanstring($value) : NEXTEUROPA_NEWSROOM_ALL;
  }

  /**
   * Gets current items.
   *
   * @return array
   *   Current agenda items.
   */
  public function getCurrentItems() {
    return $this->currentItems;
  }

  /**
   * Sets current items.
   *
   * @param array $value
   *   Current agenda items.
   */
  public function setCurrentItems($value) {
    $this->currentItems = $this->sortItems($value);
  }

  /**
   * Gets upcoming items.
   *
   * @return array
   *   Upcoming agenda items.
   */
  public function getUpcomingItems() {
    return $this->upcomingItems;
  }

  /**
   * Sets upcoming items.
   *
   * @param array $value
   *    Upcoming agenda items.
   */
  public function setUpcomingItems($value) {
    $this->upcomingItems = $this->sortItems($value);
  }

  /**
   * Gets upcoming date.
   *
   * @return object
   *   Upcoming date.
   */
  public function getUpcomingDate() {
    return $this->upcomingDate;
  }

  /**
   * Sets upcoming date.
   *
   * @param object $value
   *   Upcoming date.
   */
  public function setUpcomingDate($value) {
    $this->upcomingDate = $value;
  }

  /**
   * Gets previous date.
   *
   * @return object
   *   Previous date.
   */
  public function getPreviousDate() {
    return $this->previousDate;
  }

  /**
   * Sets previous date.
   *
   * @param object $value
   *   Previous date.
   */
  public function setPreviousDate($value) {
    $this->previousDate = $value;
  }

  /**
   * Gets current date.
   *
   * @return Datetime
   *   Current date.
   */
  public function getCurrentDate() {
    return $this->currentDate;
  }

  /**
   * Sets current date.
   *
   * @param object $value
   *   Current date.
   */
  public function setCurrentDate($value) {
    $value->setTime(0, 0, 0);
    $this->currentDate = $value;
  }

  /**
   * Gets query object.
   *
   * @return object
   *   Query object.
   */
  public function getQuery() {
    return $this->query;
  }

  /**
   * Sets query object.
   *
   * @param object $value
   *   Query object.
   */
  public function setQuery($value) {
    $this->query = $value;
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
   * Sets DB data results.
   */
  public function setResult() {
    $cache_key = 'result:' . md5($this->getUniqueCachePart());
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $this->getBaseQuery();
      $data = $this->prepareResult($this->loadResult());
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_agenda_result', 3600));
    }

    $this->result = $data;
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
   * Sets topics.
   *
   * @param array $value
   *   Newsroom topic terms array.
   */
  public function setTopics($value) {
    $this->topics = $value;
  }

  /**
   * Gets topics.
   *
   * @return array
   *   Newsroom topic terms array.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Adds item count.
   *
   * @param int $value
   *   Number of agenda items.
   */
  public function addItemsCount($value) {
    $this->itemsCount += $value;
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
   * Prepares agenda components: query, result, the dates range.
   */
  protected function prepareAgenda() {
    $this->setResult();
    $this->setupAgenda();
  }

  /**
   * Returns previous title.
   *
   * @return string
   *   Title.
   */
  public function getPreviousTitle() {
    return t('Previous');
  }

  /**
   * Returns next title.
   *
   * @return string
   *   Title.
   */
  public function getNextTitle() {
    return t('Next');
  }

  /**
   * Returns form rendable array by ID.
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
    return drupal_get_form($form_id, $this->getView(), $this->getTypeId(), $topic_id, $this->getCurrentDate()->format(NewsroomAgenda::DATE_FORMAT), $result_topics);
  }

  /**
   * Returns the agenda html.
   *
   * @return string
   *   HTML.
   */
  public function getAgenda() {
    $this->prepareAgenda();
    $filter_form = $this->getForm('nexteuropa_newsroom_agenda_filter_form');
    $date_form = $this->getForm('nexteuropa_newsroom_agenda_datepicker_form');
    $date_form_output = $this->getDisplayCalendar() ? drupal_render($date_form) : NULL;
    $content = theme('newsroom_agenda_page', array(
      'filter_form' => drupal_render($filter_form),
      'date_form' => $date_form_output,
      'items' => $this->prepareItemsOutput($this->getCurrentItems()),
      'next_event_items' => $this->prepareItemsOutput($this->getUpcomingItems()),
      'is_block' => $this->getIsBlock(),
      'navigation' => array(
        'previous' => $this->getPreviousDate() ? $this->getNavigationLink($this->getPreviousTitle(), $this->getPreviousDate()) : NULL,
        'next' => $this->getUpcomingDate() ? $this->getNavigationLink($this->getNextTitle(), $this->getUpcomingDate()) : NULL,
      ),
    ));
    return $content;
  }

  /**
   * Prepares agenda items for presenation.
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
      foreach ($item->getItems() as $agenda_item) {
        $agenda_item->prepared_start_date = $agenda_item->start_date_obj->format('d/m/Y');
        $agenda_item->prepared_end_date = $agenda_item->end_date_obj->format('d/m/Y');
      }
      $output .= theme('newsroom_agenda_items', array(
        'date' => theme('newsroom_agenda_date', array(
          'day' => $item->getDate()->format('d'),
          'month' => drupal_strtoupper($item->getDate()->format('M')),
          'year' => $item->getDate()->format('Y'),
        )),
        'items' => $item->getItems(),
      ));
    }
    return $output;
  }

  /**
   * Generates content for Agenda block.
   *
   * @return string
   *   Content of the agenda block.
   */
  public function getBlockAgenda() {
    $cache_key = 'get_agenda:block:' . $this->getUniqueCachePart();
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $content = $cache->data;
    }
    else {
      $this->prepareAgenda();
      $content = theme('newsroom_agenda_page', array(
        'filter_form' => NULL,
        'date_form' => NULL,
        'items' => $this->prepareItemsOutput($this->getCurrentItems()),
        'next_event_items' => $this->prepareItemsOutput($this->getUpcomingItems()),
        'is_block' => $this->getIsBlock(),
        'navigation' => array(),
      ));
      cache_set($cache_key, $content, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_agenda_block', 90));
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
    return md5($this->getCurrentDate()->format(NewsroomAgenda::DATE_FORMAT) . $this->getTypeId() . implode('', $this->getTopicsId()));
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
    $query->condition('n.type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    $events_term_ids = NewsroomHelper::getEventsTermsIds();
    if ($events_term_ids) {
      $query->condition('tf.field_newsroom_item_type_tid', $events_term_ids);
    }

    $query->orderBy('d.field_newsroom_item_date_value');
    $query->orderBy('d.field_newsroom_item_date_value2');

    if ($this->getTypeId()) {
      $query->condition('tt.tid', NewsroomHelper::getTypeChildren($this->getTypeId()));
    }

    $this->setQuery($this->processQuery($query));
  }

  /**
   * Processes query before execution.
   *
   * @param object $query
   *   Query object.
   *
   * @return object
   *   Query object.
   */
  protected function processQuery($query) {
    if (count($this->getTopics()) > 0) {
      $query->condition('topic_data.tid', $this->getTopicsId());
    }
    return $query;
  }

  /**
   * Builds the agenda array based on the end and start date.
   *
   * @param object $start_input_date
   *   Start date.
   * @param object $end_input_date
   *   End date.
   * @param bool $build_empty_days
   *   Add empty days or not.
   *
   * @return array
   *   Agenda items events.
   */
  public function buildAgenda($start_input_date, $end_input_date, $build_empty_days = TRUE) {
    $start_date = clone $start_input_date;
    $end_date = clone $end_input_date;
    $output = array();

    $cache_key = 'get_agenda:build:' . $this->getUniqueCachePart() . $start_input_date->getTimestamp() . $end_input_date->getTimestamp();

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $output = $cache->data;
    }
    else {
      $items = $this->getResult();
      while ($start_date < $end_date) {
        $agenda_item = new NewsroomAgendaItem();
        $agenda_item->setDate(clone $start_date);

        foreach ($items as $item) {
          if ($item->start_date_obj <= $start_date && $item->end_date_obj >= $start_date) {
            $agenda_item->addItem($item);
          }
        }

        if ($build_empty_days || (!$build_empty_days && (count($agenda_item->getItems()) > 0))) {
          $output[] = $agenda_item;
        }

        $start_date->modify('+1 day');
      }
      cache_set($cache_key, $output, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_agenda_build', 3600));
    }

    // Calculate total number of events in agenda, so we will display too many
    // or addtional events from the future days.
    $this->getBuildItemsCount($output);
    return $output;
  }

  /**
   * Gets build items count.
   *
   * @param array $output
   *   Array of Agenda items.
   */
  protected function getBuildItemsCount($output) {
    foreach ($output as $item) {
      $this->addItemsCount(count($item->getItems()));
    }
  }

  /**
   * Converts string to date object and fill empty dates.
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
   * @param object $date
   *   Datetime object.
   *
   * @return string|null
   *   HTML link.
   */
  protected function getNavigationLink($title, $date) {
    return $date ? l($title, $this->getNavigationUrl($date)) : NULL;
  }

  /**
   * Returns agenda navigation URL.
   *
   * @param object $date
   *   Datetime object.
   *
   * @return string
   *   URL string.
   */
  public function getNavigationUrl($date) {
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
    $cache_key = 'get_agenda:current_items:' . $this->getUniqueCachePart();
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $current_items = $cache->data;
    }
    else {
      $current_items = $this->buildAgenda($this->getCurrentDate(), $this->getUpcomingDate());
      cache_set($cache_key, $current_items, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_current_items', 3600));
    }
    $this->setCurrentItems($current_items);
  }

  /**
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    $end_date_condition = db_and()
      ->condition('d.field_newsroom_item_date_value2', $this->getCurrentDate()->format(NewsroomAgenda::DATE_FORMAT), '>=')
      ->condition('d.field_newsroom_item_date_value', $this->getUpcomingDate()->format(NewsroomAgenda::DATE_FORMAT), '<=');

    $start_date_condition = db_and()
      ->condition('d.field_newsroom_item_date_value', $this->getCurrentDate()->format(NewsroomAgenda::DATE_FORMAT), '>=')
      ->condition('d.field_newsroom_item_date_value', $this->getUpcomingDate()->format(NewsroomAgenda::DATE_FORMAT), '<=')
      ->isNull('d.field_newsroom_item_date_value2');

    $date_condition = db_or();
    $date_condition->condition($end_date_condition);
    $date_condition->condition($start_date_condition);

    $this->getQuery()->condition($date_condition);
    return $this->getQuery()->execute()->fetchAll();
  }

  /**
   * Sorts agenda items.
   *
   * @param array $items
   *   Agenda items array.
   *
   * @return array
   *   Sorted agenda items array.
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
   * Gets IDs array from topics array.
   *
   * @return array
   *   Array of topic IDs.
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
   * Gets IDs array from topics array.
   *
   * @return array
   *   Array of IDs.
   */
  protected function getResultTopicsId() {
    $cache_key = 'result_topics';
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $tids = $cache->data;
    }
    else {
      $query = db_select('node', 'n');
      $query->distinct();
      $query->fields('topic_field', array('tid' => 'field_newsroom_topics_tid'));
      $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
      $query->join('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
      $query->condition('n.status', 1);
      $events_term_ids = NewsroomHelper::getEventsTermsIds();
      if ($events_term_ids) {
        $query->condition('tf.field_newsroom_item_type_tid', $events_term_ids);
      }
      $tids = $query->execute()->fetchAllKeyed(0, 0);
      cache_set($cache_key, $tids, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_result_topics', 86400));
    }
    return $tids;
  }

  /**
   * Adds date url parts.
   *
   * @param object $date
   *   The current date.
   */
  abstract protected function setUrlItems($date);

}
