<?php

namespace Drupal\tmgmt_dgt_connector_cart\Entity;

use Entity;

/**
 * DGT FTT Translator mapping entity.
 */
class CartBundle extends Entity {

  /**
   * Override the save to update date properties.
   */
  public function save() {

    if (empty($this->created)) {
      $this->created = REQUEST_TIME;
    }

    $this->changed = REQUEST_TIME;

    $return = parent::save();
    return $return;
  }

  /**
   * {@inheritdoc}
   */
  public function discard() {
    $this->discardRelatedItems();
  }

  private function discardRelatedItems(){
    foreach ($this->getRelatedItems() as $item) {
    }
  }

  private function getRelatedItems(){
    return array();
  }
}
