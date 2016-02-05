<?php

/**
 * @file
 * Code for the NewsroomAgendaSchedule class.
 */

/**
 * NewsroomAgendaSchedule class.
 */
class NewsroomAgendaBlockSchedule extends NewsroomAgendaSchedule {
  const ITEMS_NUMBER = 3;
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

  private $operator = 'OR';

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
    return $this->operator = $value;
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

    if (count($this->getTopics()) == 0) {
      return $query;
    }

    $topic_ids = $this->getTopicsId();

    if ($this->getOperator() == 'OR') {
      $query->condition('topic_data.tid', $topic_ids);
    } else {

      $sub_query = db_select('field_data_field_newsroom_topics', 'ttopic');
      $sub_query->addExpression('count(ttopic.field_newsroom_topics_tid)', 'cnt');
      $sub_query->condition('field_newsroom_topics_tid', $topic_ids);
      $sub_query->groupBy('ttopic.field_newsroom_topics_tid');

      $query->condition(count($this->getTopics()), $sub_query, '=');
    }

    return $query;
  }

}
