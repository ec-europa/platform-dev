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
   * @param DateTime $current_month
   *   Current month.
   */
  public function __construct($type, $topics, DateTime $current_month) {
    $this->setView('month');
    $this->setCurrentDate($current_month);

    $next_month = clone $current_month;
    $next_month->modify('+1 month');
    $this->setNextDate($next_month);

    $previous_month = clone $current_month;
    $previous_month->modify('-1 month');
    $this->setPreviousDate($previous_month);

    $this->setDisplayCalendar(FALSE);

    parent::__construct($type, $topics);
  }

  /**
   * Adds date url parts.
   *
   * @param DateTime $date
   *   The current date.
   */
  protected function setUrlItems(DateTime $date) {
    if ($date) {
      $this->addUrlPart($date->format('n'));
      $this->addUrlPart($date->format('Y'));
    }
  }

}
