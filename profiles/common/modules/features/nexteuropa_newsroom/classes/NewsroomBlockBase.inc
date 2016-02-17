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
   * Getter.
   */
  public function getHighlighted() {
    return $this->highlighted;
  }

  /**
   * Getter.
   */
  public function getLatestDate() {
    return $this->lastest_date;
  }

  /**
   * Setter.
   */
  public function setLatestDate($value) {
    $this->lastest_date = $value;
  }

  /**
   * Getter.
   */
  public function getIsAgenda() {
    return $this->is_agenda;
  }

  /**
   * Setter.
   */
  public function setIsAgenda($value) {
    $this->is_agenda = $value;
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
   * Getter.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Setter.
   */
  public function setType($value) {
    $this->type = $value;
  }

  /**
   * Getter.
   */
  public function getTopics() {
    return $this->topics;
  }

  /**
   * Setter.
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
   * Setter.
   */
  public function getTypeUrl() {
    return $this->getType() ? pathauto_cleanstring(NewsroomHelper::getTermTranslatedName($this->getType())) : 'all';
  }

  /**
   * Setter.
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
