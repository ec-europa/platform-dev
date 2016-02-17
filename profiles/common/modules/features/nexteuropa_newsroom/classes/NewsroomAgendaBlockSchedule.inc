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
   * NewsroomAgendaSchedule constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param DateTime $current_day
   *   Current date.
   */
  public function __construct($type, $topics, DateTime $current_day, $operator) {
    $this->setIsBlock(TRUE);
    $this->setOperator($operator);
    parent::__construct($type, $topics, $current_day);
  }

  /**
   * Returns the number of items per block.
   *
   * @return int
   *   Number of items.
   */
  public function getItemsNumber() {
    return NewsroomHelper::getBlockItemsNumber(FALSE);
  }

  /**
   * Getter.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Setter.
   */
  public function setOperator($value) {
    $this->operator = $value;
  }

  /**
   * Preprocessing of the query before the execution.
   *
   * @param object $query
   *   Query object.
   *
   * @return object
   *   Query object.
   */
  protected function processQuery($query) {

    if (count($this->getTopics()) == 0) {
      return $query;
    }

    $topic_ids = $this->getTopicsId();
    if ($this->getOperator() == 'OR') {
      $query->condition('topic_data.tid', $topic_ids);

    }
    else {
      $nids = NewsroomHelper::getNodeRelatedToTopic($this->getTopicsId());
      if ($nids) {
        $query->condition('nid', $nids, 'IN');
      }
    }

    return $query;
  }

}
