<?php

namespace Drupal\tmgmt_dgt_connector_cart\Entity;

use Entity;

/**
 * DGT FTT Translator mapping entity.
 */
class CartBundle extends Entity {

  /**
   * Override the save to add clearing of caches
   */
  public function save() {

    if (empty($this->created)) {
      $this->created = REQUEST_TIME;
    }

    $this->changed = REQUEST_TIME;

    $this->plugin->submit($this);

    $return = parent::save();
    return $return;
  }
}
