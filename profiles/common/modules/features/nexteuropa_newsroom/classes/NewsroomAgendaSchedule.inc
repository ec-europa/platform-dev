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
   * Getter.
   */
  public function getLastAgendaDate() {
    return $this->lastAgendaDate;
  }

  /**
   * Setter.
   */
  public function setLastAgendaDate($value) {
    $this->lastAgendaDate = $value;
  }

  /**
   * NewsroomAgendaSchedule constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param DateTime $current_day
   *   Current date.
   */
  public function __construct($type, $topics, DateTime $current_day) {
    $this->setCurrentDate($current_day);
    parent::__construct($type, $topics);
  }

  /**
   * Setups agenda conditions.
   */
  protected function setupAgenda() {
    $next_day = clone $this->getCurrentDate();
    // Build agenda for the current date.
    $next_day->modify('+1 day');
    $this->setCurrentItems($this->buildAgenda($this->getCurrentDate(), $next_day));
    $this->findNextItems();
    $this->findPreviousDate();
    $this->findNextDate();
  }

  /**
   * Adds date url parts.
   *
   * @param DateTime $date
   *   The current date.
   */
  protected function setUrlItems(DateTime $date) {
    if ($date) {
      $this->addUrlPart($date->format('j'));
      $this->addUrlPart($date->format('n'));
      $this->addUrlPart($date->format('Y'));
    }
  }

  /**
   * Finds and set next items from the current items.
   */
  protected function findNextItems() {
    $start_date = clone $this->getCurrentDate();
    // We start from the next day after the current.
    $start_date->modify('+1 day');
    $this->setLastAgendaDate($start_date);
    $next_items = array();
    // We add one day to include the last day also.
    $last_event_date = $this->getUtmostDate(FALSE);
    if ($last_event_date) {
      $last_event_date->modify('+1 day');
      $number_to_display = $this->getItemsNumber();
      while ($this->getItemsCount() < $number_to_display && $start_date <= $last_event_date) {
        $next_day = clone $start_date;
        $next_day->modify('+1 day');
        $current_items = $this->buildAgenda($start_date, $next_day, FALSE);
        $next_items = array_merge($next_items, $current_items);

        $this->setLastAgendaDate($start_date);
        $start_date->modify('+1 day');
      }
    }

    $this->setNextItems($next_items);
  }

  /**
   * Check agenda items for existence of events.
   *
   * @param array $items
   *   Agenda items.
   *
   * @return bool
   *   Has events.
   */
  protected function hastItems($items) {
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
   * Finds and set next date for the current items.
   */
  protected function findNextDate() {
    $last_agenda_date = $this->getLastAgendaDate();

    $next_items = array();
    // We add one day to include the last day also.
    $last_event_date = $this->getUtmostDate(FALSE);
    if ($last_agenda_date && $last_event_date) {
      // We start from the next day after the current.
      $start_date = clone $last_agenda_date;

      $last_event_date->modify('+1 day');
      while ($start_date <= $last_event_date) {
        $next_day = clone $start_date;
        $next_day->modify('+1 day');
        $next_items = $this->buildAgenda($start_date, $next_day);
        if ($this->hastItems($next_items)) {
          $this->setNextDate($start_date);
          break;
        }

        $start_date->modify('+1 day');
      }
    }
  }

  /**
   * Finds and set previous date for the current items.
   */
  protected function findPreviousDate() {
    $start_date = clone $this->getCurrentDate();
    $first_event_date = $this->getUtmostDate();
    if ($first_event_date) {
      while ($start_date > $first_event_date) {
        $previous_day = clone $start_date;
        $previous_day->modify('-1 day');
        $previous_items = $this->buildAgenda($previous_day, $start_date);
        if ($this->hastItems($previous_items)) {
          $this->setPreviousDate($previous_day);
          break;
        }

        $start_date->modify('-1 day');
      }
    }
  }

  /**
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    $cache_key = 'schedule_result:' . md5($this->getQuery());
    $cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE);
    if ($cache) {
      $data = $cache->data;
    }
    else {
      $data = $this->getQuery()->execute()->fetchAll();
      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + 3600);
    }
    return $data;
  }

  /**
   * Get Utmost date for the current items.
   *
   * @param bool $first
   *   Return the first or last.
   *
   * @return DateTime
   *   Utmost date.
   */
  protected function getUtmostDate($first = TRUE) {
    $last_date = NULL;
    $result = $this->getResult();
    $last_item = $first ? reset($result) : array_pop($result);
    if ($last_item) {
      $last_date = !empty($last_item->end_date) ? clone $last_item->end_date_obj : clone $last_item->start_date_obj;
    }
    return $last_date;
  }

}
