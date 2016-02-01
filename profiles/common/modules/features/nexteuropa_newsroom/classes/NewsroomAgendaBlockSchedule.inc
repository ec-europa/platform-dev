<?php
/**
 * @file
 * Code for the NewsroomAgendaSchedule class.
 */

/**
 * NewsroomAgendaSchedule class.
 */
class NewsroomAgendaBlockSchedule extends NewsroomAgendaSchedule {
  private $operator = 'OR';

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
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    return $this->getQuery()->execute()->fetchAll();
  }

  protected function processQuery($query) {
    if (count($this->getTopics()) > 0) {
      $query->condition('topic_data.tid', $this->getTopics());
    }
    return $query;
  }

}
