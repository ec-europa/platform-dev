<?php

namespace Drupal\tmgmt_dgt_connector_cart\Entity;

use Entity;
use EntityFieldQuery;

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
   * Load a cart bundle entity from the database.
   */
  public static function load($cbid, $reset) {
    $cbids = (isset($cbid) ? array($cbid) : array());
    $cart_bundle = self::loadMultiple($cbids, $reset);
    return $cart_bundle ? reset($cart_bundle) : FALSE;
  }

  /**
   * Load cart bundle entities from the database.
   */
  public static function loadMultiple($cbids, $reset = FALSE) {
    return entity_load('cart_bundle', $cbids, array(), $reset);
  }

  /**
   * Load cart bundle entities filtered by a set of properties.
   */
  public static function loadWithProperties($properties) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'cart_bundle');
    foreach ($properties as $property => $value) {
      $query->propertyCondition($property, $value);
    }

    $result = $query->execute();
    if (isset($result['cart_bundle'])) {
      $cbids = array_keys($result['cart_bundle']);
      return self::loadMultiple($cbids);
    }
    return array();
  }

  /**
   * Create a cart bundle entity.
   */
  public static function create($uid, $target_languages, $status, $tjid = 0) {
    $cart_bundle = entity_create(
      'cart_bundle',
      array(
        'uid' => $uid,
        'tjid' => $tjid,
        'target_languages' => $target_languages,
        'status' => $status,
      )
    );
    $cart_bundle->save();
    return $cart_bundle;
  }

}
