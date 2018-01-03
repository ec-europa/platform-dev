<?php

namespace Drupal\tmgmt_dgt_connector_cart\Entity;

use Entity;
use EntityFieldQuery;

/**
 * DGT FTT Translator mapping entity.
 */
class CartItem extends Entity {

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
   * Load a cart item entity from the database.
   */
  public static function load($ciid, $reset) {
    $ciids = (isset($ciid) ? array($ciid) : array());
    $cart_bundle = self::loadMultiple($ciids, $reset);
    return $cart_bundle ? reset($cart_bundle) : FALSE;
  }

  /**
   * Load cart item entities from the database.
   */
  public static function loadMultiple($ciids, $reset = FALSE) {
    return entity_load('cart_item', $ciids, array(), $reset);
  }

  /**
   * Load cart item entities filtered by a set of properties.
   */
  public static function loadWithProperties($properties) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'cart_item');
    foreach ($properties as $property => $value) {
      $query->propertyCondition($property, $value);
    }

    $result = $query->execute();
    if (isset($result['cart_item'])) {
      $cbids = array_keys($result['cart_item']);
      return self::loadMultiple($cbids);
    }
    return array();
  }

  /**
   * Create a cart item entity.
   */
  public static function create($cbid, $entity_type, $entity_id, $context_url = '', $context_comment = '', $tjiid = 0) {
    $cart_item = entity_create(
      'cart_item',
      array(
        'cbid' => $cbid,
        'entity_type' => $entity_type,
        'entity_id' => $entity_id,
        'context_url' => $context_url,
        'context_comment' => $context_comment,
        'tjiid' => $tjiid,
      )
    );
    $cart_item->save();
    return $cart_item;
  }

}
