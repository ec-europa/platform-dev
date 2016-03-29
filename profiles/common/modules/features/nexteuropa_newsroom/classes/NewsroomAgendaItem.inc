<?php

/**
 * @file
 * TBC.
 */

/**
 * Description of NewsroomAgenda.
 */
class NewsroomAgendaItem {

  protected $items = array();
  protected $date = NULL;

  /**
   * Gets agenda items.
   */
  public function getItems() {
    return $this->items;
  }

  /**
   * Sets agenda items.
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
    $this->items[] = $value;
  }

  /**
   * Gets agenda date.
   */
  public function getDate() {
    return $this->date;
  }

  /**
   * Sets agenda date.
   */
  public function setDate($value) {
    $this->date = $value;
  }

}
