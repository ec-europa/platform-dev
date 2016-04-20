<?php

/**
 * @file
 * Code for the NewsroomAgendaBlockSchedule class.
 */

/**
 * NewsroomAgendaBlockSchedule class.
 */
class NewsroomAgendaBlockSchedule extends NewsroomAgendaSchedule {
  private $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;

  /**
   * NewsroomAgendaBlockSchedule constructor.
   *
   * @param object $type
   *   Newsroom type taxonomy term.
   * @param array $topics
   *   Newsroom topic taxonomy term.
   * @param object $current_day
   *   Current date.
   */
  public function __construct($type, $topics, $current_day, $operator) {
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
   * Gets query operator.
   *
   * @return string
   *   Query operator: OR or AND.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Sets query operator.
   *
   * @param string $value
   *   Query operator: OR or AND.
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
    if ($this->getOperator() == NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
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
