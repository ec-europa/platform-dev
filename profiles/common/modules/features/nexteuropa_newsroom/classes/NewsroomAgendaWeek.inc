<?php

/**
 * @file
 * Code for the NewsroomAgendaWeek class.
 */

/**
 * Description of NewsroomAgendaWeek.
 */
class NewsroomAgendaWeek extends NewsroomAgenda {

  /**
   * NewsroomAgendaWeek constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topics.
   * @param object $current_day
   *   Current month.
   */
  public function __construct($type, $topics, $current_day) {
    $this->setView('week');
    $this->setCurrentDate($current_day);

    $next_day = clone $current_day;
    $next_day->modify('+7 day');
    $this->setUpcomingDate($next_day);

    $previous_day = clone $current_day;
    $previous_day->modify('-7 day');
    $this->setPreviousDate($previous_day);

    $this->setDisplayCalendar(FALSE);

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
      $this->addUrlPart((int) $date->format('W'));
      $this->addUrlPart($date->format('Y'));
    }
  }

}
