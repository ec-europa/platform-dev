<?php

/**
 * @file
 * Code for the NewsroomAgendaSchedule class.
 */

/**
 * NewsroomAgendaSchedule class.
 */
class NewsroomAgendaSchedule extends NewsroomAgenda {

  protected $lastAgendaDate = NULL;

  /**
   * NewsroomAgendaSchedule constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param object $current_day
   *   Current date.
   */
  public function __construct($type, $topics, $current_day) {
    $this->setCurrentDate($current_day);
    parent::__construct($type, $topics);
  }

  /**
   * Gets the latest date in the agenda.
   *
   * @return Datetime
   *   Latest date in the agenda.
   */
  public function getLastAgendaDate() {
    return $this->lastAgendaDate;
  }

  /**
   * Sets the latest date in the agenda.
   *
   * @param object $value
   *   Latest date in the agenda.
   */
  public function setLastAgendaDate($value) {
    $this->lastAgendaDate = $value;
  }

  /**
   * Setups agenda conditions.
   */
  protected function setupAgenda() {
    $next_day = clone $this->getCurrentDate();
    // Build agenda for the current date.
    $next_day->modify('+1 day');
    $this->setCurrentItems($this->buildAgenda($this->getCurrentDate(), $next_day));
    $this->setLastAgendaDate($next_day);
    $this->findUpcomingItems();
    // We don't need navigation for the blocks.
    if (!$this->getIsBlock()) {
      $this->findPreviousDate();
      $this->findUpcomingDate();
    }
  }

  /**
   * Adds date url parts.
   *
   * @param object $date
   *   The current date.
   */
  protected function setUrlItems($date) {
    if ($date) {
      $this->addUrlPart($date->format('j'));
      $this->addUrlPart($date->format('n'));
      $this->addUrlPart($date->format('Y'));
    }
  }

  /**
   * Finds and sets upcoming items.
   */
  protected function findUpcomingItems() {
    $start_date = clone $this->getCurrentDate();
    // We start from the next day after the current.
    $start_date->modify('+1 day');
    $this->setLastAgendaDate($start_date);
    $upcoming_items = array();
    // We add one day to include the last day also.
    $last_event_date = $this->getUtmostDate(FALSE);
    if ($last_event_date) {
      $last_event_date->modify('+1 day');
      $number_to_display = $this->getItemsNumber();
      while ($this->getItemsCount() < $number_to_display && $start_date <= $last_event_date) {
        $next_day = clone $start_date;
        $next_day->modify('+1 day');
        $current_items = $this->buildAgenda($start_date, $next_day, FALSE);
        $upcoming_items = array_merge($upcoming_items, $current_items);
        $this->setLastAgendaDate($start_date);
        $start_date->modify('+1 day');
      }
    }
    $this->setUpcomingItems($upcoming_items);
  }

  /**
   * Checks agenda items for existence of events.
   *
   * @param array $items
   *   Agenda items.
   *
   * @return bool
   *   Has events.
   */
  protected function hasItems($items) {
    $has_current_items = FALSE;
    if ($items) {
      foreach ($items as $item) {
        if (count($item->getItems()) > 0) {
          $has_current_items = TRUE;
          break;
        }
      }
    }
    return $has_current_items;
  }

  /**
   * Finds and set upcoming date.
   */
  protected function findUpcomingDate() {
    $cache_key = 'get_agenda:upcoming_date:' . $this->getUniqueCachePart();

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $upcoming_date = $cache->data;
    }
    else {
      $last_agenda_date = $this->getLastAgendaDate();
      $upcoming_items = array();
      // We add one day to include the last day also.
      $last_event_date = $this->getUtmostDate(FALSE);

      $upcoming_date = NULL;
      if ($last_agenda_date && $last_event_date) {
        // We start from the next day after the current.
        $start_date = clone $last_agenda_date;
        $last_event_date->modify('+1 day');
        while ($start_date <= $last_event_date) {
          $next_day = clone $start_date;
          $next_day->modify('+1 day');
          $upcoming_items = $this->buildAgenda($start_date, $next_day);
          if ($this->hasItems($upcoming_items)) {
            $upcoming_date = $start_date;
            break;
          }

          $start_date->modify('+1 day');
        }
      }
      cache_set($cache_key, $upcoming_date, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_upcoming_date', 3600));
    }

    $this->setUpcomingDate($upcoming_date);
  }

  /**
   * Finds and sets previous date.
   */
  protected function findPreviousDate() {
    $cache_key = 'get_agenda:previous_date:' . $this->getUniqueCachePart();

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $previous_day = $cache->data;
    }
    else {
      $start_date = clone $this->getCurrentDate();
      $first_event_date = $this->getUtmostDate();
      $previous_day = NULL;
      if ($first_event_date) {
        while ($start_date > $first_event_date) {
          $previous_date = clone $start_date;
          $previous_date->modify('-1 day');
          $previous_items = $this->buildAgenda($previous_date, $start_date);
          if ($this->hasItems($previous_items)) {
            $previous_day = $previous_date;
            break;
          }

          $start_date->modify('-1 day');
        }
      }
      cache_set($cache_key, $previous_day, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_previous_date', 3600));
    }

    $this->setPreviousDate($previous_day);
  }

  /**
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    return $this->getQuery()->execute()->fetchAll();;
  }

  /**
   * Gets utmost date.
   *
   * @param bool $first
   *   Return the first or last.
   *
   * @return object
   *   Utmost date.
   */
  protected function getUtmostDate($first = TRUE) {
    $last_date = NULL;
    $result = $this->getResult();
    $last_item = $first ? reset($result) : array_pop($result);
    if ($last_item) {
      $last_date = clone $last_item->start_date_obj;
    }
    return $last_date;
  }

}
