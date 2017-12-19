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

}
