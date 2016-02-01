<?php
/**
 * @file
 * Code for the NewsroomAgenda class.
 */

/**
 * NewsroomAgenda class base class.
 */
abstract class NewsroomAgenda {
  const ITEMS_NUMBER = 10;
  private $view = 'schedule';
  private $topicUrl = 'all';
  private $topics = array();
  private $typeUrl = 'all';
  private $typeId = NULL;
  private $currentDate = NULL;
  private $nextDate = NULL;
  private $previousDate = NULL;
  private $currentItems = array();
  private $nextItems = array();
  private $result = array();
  private $query = NULL;
  private $itemsCount = 0;
  private $urlParts = array();
  private $displayCalendar = TRUE;

  /**
   * Getter.
   */
  public function getDisplayCalendar() {
    return $this->displayCalendar;
  }

  /**
   * Setter.
   */
  public function setDisplayCalendar($value) {
    return $this->displayCalendar = $value;
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
    return $this->view = $value;
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
    return $this->topicUrl = !empty($value) ? pathauto_cleanstring($value) : 'all';
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
    return $this->typeUrl = !empty($value) ? pathauto_cleanstring($value) : 'all';
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
    return $this->currentItems = $this->sortItems($value);
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
    return $this->nextItems = $this->sortItems($value);
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
    return $this->nextDate = $value;
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
    return $this->previousDate = $value;
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
    return $this->currentDate = $value;
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
    return $this->query = $value;
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
    return $this->result = $value;
  }

  /**
   * Setter.
   */
  public function setTypeId($value) {
    return $this->typeId = $value;
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
    return $this->topics = $value;
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
   * @param mix $topics
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
    return drupal_get_form($form_id, $this->getView(), $this->getTypeId(), $topic_id, $this->getCurrentDate()->format('Y-m-d'));
  }

  /**
   * Returns the agenda html.
   *
   * @return string
   *   HTML.
   */
  public function getAgenda() {
    $this->prepareAgenda();
    return theme('newsroom_agenda_page', array(
      'filter_form' => $this->getForm('nexteuropa_newsroom_agenda_filter_form'),
      'date_form' => $this->getDisplayCalendar() ? $this->getForm('nexteuropa_newsroom_agenda_datepicker_form') : NULL,
      'items' => $this->getCurrentItems(),
      'next_event_items' => $this->getNextItems(),
      'navigation' => array(
        'previous' => $this->getPreviousDate() ? $this->getNavigationLink($this->getPreviousTitle(), $this->getPreviousDate()) : NULL,
        'next' => $this->getNextDate() ? $this->getNavigationLink($this->getNextTitle(), $this->getNextDate()) : NULL,
      ),
    ));
  }
  
  public function getBlockAgenda() {
    $this->prepareAgenda();
    return theme('newsroom_agenda_page', array(
      'filter_form' => NULL,
      'date_form' => NULL,
      'items' => $this->getCurrentItems(),
      'next_event_items' => $this->getNextItems(),
      'navigation' => array(),
    ));
  }

  /**
   * Returns the base query.
   */
  public function getBaseQuery() {
    $events_taxonomy_terms = NewsroomHelper::getEventsTermsIds();

    $query = db_select('node', 'n');
    $query->distinct();
    $query->fields('n', array('nid', 'title'));
    $query->fields('tt', array('name'));
    $query->addField('tt', 'tid', 'typeId');
    $query->addField('d', 'field_newsroom_item_date_value', 'start_date');
    $query->addField('d', 'field_newsroom_item_date_value2', 'end_date');
    $query->join('field_data_field_newsroom_item_date', 'd', 'd.entity_id = n.nid');
    $query->join('field_data_field_newsroom_item_type', 'tf', 'tf.entity_id = n.nid');
    $query->join('taxonomy_term_data', 'tt', 'tt.tid = tf.field_newsroom_item_type_tid');
    $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
    $query->leftJoin('taxonomy_term_data', 'topic_data', 'topic_data.tid = topic_field.field_newsroom_topics_tid');
    $query->condition('n.status', 1);
    $query->condition('tf.field_newsroom_item_type_tid', $events_taxonomy_terms);
    $query->orderBy('d.field_newsroom_item_date_value');
    $query->orderBy('d.field_newsroom_item_date_value2');

    if ($this->getTypeId()) {
      $query->condition('tt.tid', NewsroomHelper::getTermChildren($this->getTypeId()));
    }
    
    if (count($this->getTopics()) > 0) {
      $query->condition('topic_data.tid', $this->getTopics());
    }

//    $query->processQuery($query);
    
    $this->setQuery($query);
  }
  
  protected function processQuery($query) {
    if (count($this->getTopics()) > 0) {
      $query->condition('topic_data.tid', $this->getTopics());
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
        if (empty($item->start_date_obj)) {
          $items[$key]->start_date_obj = !empty($item->start_date) ? new DateTime($item->start_date) : NULL;
          $items[$key]->start_date_obj->setTime(0, 0, 0);
        }
        // If the end date is empty, it means it is one day event and we set the
        // end date to start date.
        if (empty($item->end_date_obj)) {
          $items[$key]->end_date_obj = !empty($item->end_date) ? new DateTime($item->end_date) : new DateTime($item->start_date);
          $items[$key]->end_date_obj->setTime(0, 0, 0);
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
   * Adds date url parts.
   */
  abstract protected function setUrlItems(DateTime $date);

}
