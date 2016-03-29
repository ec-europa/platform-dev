<?php

/**
 * @file
 * Code for the NewsroomBlockBase class.
 */

/**
 * NewsroomBlockBase class base class.
 */
abstract class NewsroomBlockBase {

  protected $highlighted = 0;
  protected $isAgenda = FALSE;
  protected $lastestDate = NULL;
  protected $type = NULL;
  protected $operator = 'OR';
  protected $topics = array();

  /**
   * Contructor of NewsroomBlock class.
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
   */
  public function getHighlighted() {
    return $this->highlighted;
  }

  /**
   * Gets the latest agenda date.
   */
  public function getLatestDate() {
    return $this->lastestDate;
  }

  /**
   * Sets the latest agenda date.
   */
  public function setLatestDate($value) {
    $this->lastestDate = $value;
  }

  /**
   * Gets is block agenda.
   */
  public function getIsAgenda() {
    return $this->isAgenda;
  }

  /**
   * Sets is bock agenda.
   */
  public function setIsAgenda($value) {
    $this->isAgenda = $value;
  }

  /**
   * Gets query operator.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Sets query operator.
   */
  public function setOperator($value) {
    $this->operator = $value;
  }

  /**
   * Gets type.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Sets type.
   */
  public function setType($value) {
    $this->type = $value;
  }

  /**
   * Gets topics.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Sets topics.
   */
  public function setTopics($value) {
    $this->topics = $value;
  }

  /**
   * Get css classes of a block.
   */
  public function getCssClasses() {
    $classes = array();
    if ($this->getHighlighted()) {
      $classes[] = 'featured';
      $classes[] = 'highlighted';
    }
    if ($this->getIsAgenda()) {
      $classes[] = 'agenda';
      $classes[] = 'highlighted';
    }

    return $classes;
  }

  /**
   * Gets type URL.
   */
  public function getTypeUrl() {
    return $this->getType() ? pathauto_cleanstring(NewsroomHelper::getTermTranslatedName($this->getType())) : 'all';
  }

  /**
   * Gets topic URL.
   */
  public function getTopicUrl() {
    $url = 'all';
    $topics = $this->getTopics();
    if (count($topics) == 1) {
      $topic = reset($topics);
      $url = pathauto_cleanstring(NewsroomHelper::getTermTranslatedName($topic));
    }

    return $url;
  }

  /**
   * Returns topics ids.
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
