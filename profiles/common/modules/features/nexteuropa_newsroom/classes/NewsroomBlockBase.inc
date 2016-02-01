<?php

/**
 * @file
 * Code for the NewsroomBlockBase class.
 */

/**
 * NewsroomBlockBase class base class.
 */
abstract class NewsroomBlockBase {

  private $topics = NULL;
  private $type = NULL;
  private $highlighted = FALSE;
  private $is_agenda = NULL;
  private $lastest_date = NULL;

  public function __construct($type, $topics) {
    $this->setType($type);
    $this->setTopics($topics);
  }

  /**
   * Getter.
   */
  public function getHighlighted() {
    return $this->highlighted;
  }
  
  public function getLatestDate() {
    return $this->lastest_date;
  }
  
  public function setLatestDate($value) {
    return $this->lastest_date = $value;
  }
  
  public function getIsAgenda() {
    return $this->is_agenda;
  }
  
  public function setIsAgenda($value) {
    return $this->is_agenda = $value;
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
    return $this->type = $value;
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
    return $this->topics = $value;
  }
  
  abstract function getTitle();
  abstract public function generateContent();
}
