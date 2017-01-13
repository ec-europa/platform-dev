<?php

/**
 * @file
 * Code for the NewsroomAgendaItem class.
 */

/**
 * NewsroomAgendaItem class.
 */
class NewsroomAgendaItem {

  protected $items = array();
  protected $date = NULL;

  /**
   * Gets agenda items.
   *
   * @return array
   *   Agenda items.
   */
  public function getItems() {
    return $this->items;
  }

  /**
   * Sets agenda items.
   *
   * @param array $value
   *   Agenda items.
   */
  public function setItems($value) {
    $this->items = $value;
  }

  /**
   * Adds item to items array.
   *
   * @param object $value
   *   DB result value.
   */
  public function addItem($value) {
    $node = node_load($value->nid);
    $value->title = $node->title;
    $value->url = NewsroomHelper::getNodeMainUrl($node);
    $this->items[] = $value;
  }

  /**
   * Gets agenda date.
   *
   * @return Datetime
   *   Agenda date.
   */
  public function getDate() {
    return $this->date;
  }

  /**
   * Sets agenda date.
   *
   * @param string $value
   *   Agenda date.
   */
  public function setDate($value) {
    $this->date = $value;
  }

}
