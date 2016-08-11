<?php

/**
 * @file
 * Code for the NewsroomAgendaMonth class.
 */

/**
 * NewsroomAgendaMonth class.
 */
class NewsroomAgendaMonth extends NewsroomAgenda {

  /**
   * NewsroomAgendaMonth constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topics.
   * @param object $current_month
   *   Current month.
   */
  public function __construct($type, $topics, $current_month) {
    $this->setView('month');
    $this->setCurrentDate($current_month);

    $next_month = clone $current_month;
    $next_month->modify('+1 month');
    $this->setUpcomingDate($next_month);

    $previous_month = clone $current_month;
    $previous_month->modify('-1 month');
    $this->setPreviousDate($previous_month);

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
      $this->addUrlPart($date->format('n'));
      $this->addUrlPart($date->format('Y'));
    }
  }

}
