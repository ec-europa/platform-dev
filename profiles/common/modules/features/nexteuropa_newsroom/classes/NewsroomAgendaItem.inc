<?php

/**
 * Description of NewsroomAgenda
 *
 */
class NewsroomAgendaItem {

  private $items = array();
  private $date = NULL;

  public function getItems() {
    return $this->items;
  }
  
  public function setItems($value) {
    return $this->items = $value;
  }
  
  public function addItem($value) {
    $this->items[] = $value;
  }
  
  public function getDate() {
    return $this->date;
  }
  
  public function setDate($value) {
    return $this->date = $value;
  }

}
