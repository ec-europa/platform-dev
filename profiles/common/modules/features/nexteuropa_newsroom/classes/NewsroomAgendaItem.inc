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
   * Getter.
   */
  public function getItems() {
    return $this->items;
  }

  /**
   * Setter.
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
   * Getter.
   */
  public function getDate() {
    return $this->date;
  }

  /**
   * Setter.
   */
  public function setDate($value) {
    $this->date = $value;
  }

}
