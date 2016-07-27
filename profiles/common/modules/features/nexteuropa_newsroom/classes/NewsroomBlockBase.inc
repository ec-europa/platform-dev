<?php

/**
 * @file
 * Code for the NewsroomBlockBase class.
 */

/**
 * NewsroomBlockBase base class.
 */
abstract class NewsroomBlockBase {

  protected $highlighted = 0;
  protected $isAgenda = FALSE;
  protected $lastestDate = NULL;
  protected $type = NULL;
  protected $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR;
  protected $topics = array();

  /**
   * Contructor of NewsroomBlockBase class.
   *
   * @param object $type
   *   Newsroom type taxonomy term.
   * @param array|object $topics
   *   Newsroom topics taxonomy terms.
   * @param string $operator
   *   Operator connecting  topics.
   */
  public function __construct($type, $topics, $operator) {
    $this->setType($type);
    $this->setTopics($topics);
    $this->setOperator($operator);
  }

  /**
   * Gets is block highlighted.
   *
   * @return bool
   *   Is block highlighted.
   */
  public function getHighlighted() {
    return $this->highlighted;
  }

  /**
   * Gets the latest agenda date.
   *
   * @return Datetime
   *   Latest date for the current agenda.
   */
  public function getLatestDate() {
    return $this->lastestDate;
  }

  /**
   * Sets the latest agenda date.
   *
   * @param object $value
   *    Latest date for the current agenda.
   */
  public function setLatestDate($value) {
    $this->lastestDate = $value;
  }

  /**
   * Gets is block agenda.
   *
   * @return bool
   *   Is block agenda.
   */
  public function getIsAgenda() {
    return $this->isAgenda;
  }

  /**
   * Sets is bock agenda.
   *
   * @param bool $value
   *   Is block agenda.
   */
  public function setIsAgenda($value) {
    $this->isAgenda = $value;
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
   * Gets type.
   *
   * @return object
   *   Type taxonomy term object.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Sets type.
   *
   * @param object $value
   *   Type taxonomy term object.
   */
  public function setType($value) {
    $this->type = $value;
  }

  /**
   * Gets topics.
   *
   * @return array
   *   Topic taxonomy terms array.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Sets topics.
   *
   * @param array $value
   *   Topic taxonomy terms array.
   */
  public function setTopics($value) {
    $this->topics = $value;
  }

  /**
   * Gets css classes of a block.
   *
   * @return array
   *   CSS classes array.
   */
  public function getCssClasses() {
    $classes = array();
    if ($this->getHighlighted()) {
      $classes[] = 'featured';
      $classes[] = 'highlighted';
    }
    elseif ($this->getIsAgenda()) {
      $classes[] = 'agenda';
      $classes[] = 'highlighted';
    }

    return $classes;
  }

  /**
   * Gets type URL.
   *
   * @return string
   *   Type URL part.
   */
  public function getTypeUrl() {
    return $this->getType() ? pathauto_cleanstring($this->getType()->name) : NEXTEUROPA_NEWSROOM_ALL;
  }

  /**
   * Gets topic URL.
   *
   * @return string
   *   Topic URL part.
   */
  public function getTopicUrl() {
    $url = NEXTEUROPA_NEWSROOM_ALL;
    $topics = $this->getTopics();
    if (count($topics) == 1) {
      $topic = reset($topics);
      $url = pathauto_cleanstring($topic->name);
    }

    return $url;
  }

  /**
   * Returns topics ids.
   *
   * @return array
   *   Topic IDs array.
   */
  protected function getTopicsId() {
    $topic_ids = array();
    foreach ($this->getTopics() as $topic) {
      $topic_ids[] = $topic->tid;
    }
    return $topic_ids;
  }

  /**
   * Returns block title.
   */
  abstract public function getTitle();

  /**
   * Generates block content.
   */
  abstract public function generateContent();

}
