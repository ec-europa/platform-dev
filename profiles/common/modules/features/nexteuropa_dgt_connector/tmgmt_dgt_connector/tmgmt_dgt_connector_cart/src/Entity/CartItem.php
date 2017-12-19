<?php

namespace Drupal\tmgmt_dgt_connector_cart\Entity;

use Entity;

/**
 * DGT FTT Translator mapping entity.
 */
class CartItem extends Entity {

  /**
   * {@inheritdoc}
   */
  public function discard() {
    $this->discardRelatedItems();
    $this->hasStatus();
  }

  private function discardRelatedItems(){
    foreach ($this->getRelatedItems() as $item){

    }
  }

  private function getRelatedItems(){

  }
}
