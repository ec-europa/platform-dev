<?php

/**
 * @file
 * Code for the NewsroomAgendaDay class.
 */

/**
 * Description of NewsroomAgendaDay.
 */
class NewsroomAgendaDay extends NewsroomAgenda {

  /**
   * NewsroomAgendaDay constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topics.
   * @param object $current_day
   *   Current day.
   */
  public function __construct($type, $topics, $current_day) {
    $this->setView('day');
    $this->setCurrentDate($current_day);

    $next_day = clone $current_day;
    $next_day->modify('+1 day');
    $this->setUpcomingDate($next_day);

    $previous_day = clone $current_day;
    $previous_day->modify('-1 day');
    $this->setPreviousDate($previous_day);

    parent::__construct($type, $topics);
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

}
