<?php

namespace Drupal\tmgmt_dgt_connector_cart\Entity;

use Entity;
use EntityFieldQuery;

/**
 * DGT FTT Translator mapping entity.
 */
class CartItem extends Entity {
  const STATUS_OPEN = 'OPEN';
  const STATUS_DISCARDED = 'DISCARDED';

  /**
   * Override the save to update date properties.
   */
  public function save() {
    if (empty($this->created)) {
      $this->created = REQUEST_TIME;
    }
    $this->changed = REQUEST_TIME;

    return parent::save();
  }

  /**
   * Load a cart item entity from the database.
   *
   * @param int $ciid
   *   The CartItem entity ID.
   * @param bool $reset
   *   Optional reset of the internal cache for the requested entity type.
   *
   * @return array
   *   An array of CartBundle entity objects indexed by their ids or an empty
   *   array if no results are found.
   */
  public static function load($ciid, $reset = FALSE) {
    $ciids = isset($ciid) ? array($ciid) : array();
    $cart_bundle = self::loadMultiple($ciids, $reset);

    return $cart_bundle ? reset($cart_bundle) : FALSE;
  }

  /**
   * Load CartItem entities from the database.
   *
   * @param array $ciids
   *   An array of CartItem entities IDs.
   * @param bool $reset
   *   Optional reset of the internal cache for the requested entity type.
   *
   * @return array
   *   An array of CartItems entity objects indexed by their ids or an empty
   *   array if no results are found.
   */
  public static function loadMultiple(array $ciids, $reset = FALSE) {
    return entity_load('cart_item', $ciids, array(), $reset);
  }

  /**
   * Load CartItem entities filtered by a set of properties.
   *
   * @param array $properties
   *   An array with properties for querying for specific entities.
   *
   * @return array
   *   An array of CartItem entity objects indexed by their IDs or an empty
   *   array if no results are found.
   */
  public static function loadWithProperties(array $properties) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'cart_item');
    foreach ($properties as $property => $value) {
      $query->propertyCondition($property, $value);
    }
    $result = $query->execute();

    if (isset($result['cart_item'])) {
      $ciids = array_keys($result['cart_item']);

      return self::loadMultiple($ciids);
    }

    return array();
  }

  /**
   * Create a CartItem entity.
   *
   * @param int $cbid
   *   The CartBundle entity ID.
   * @param string $entity_type
   *   An entity type.
   * @param string $entity_id
   *   An entity ID.
   * @param string $entity_title
   *   An entity title.
   * @param string $context_url
   *   A context URL.
   * @param string $context_comment
   *   A context comment.
   *
   * @return bool|CartItem
   *   A new instance of the CartItem entity or FALSE.
   */
  public static function create($cbid, $entity_type, $entity_id, $entity_title = '', $context_url = '', $context_comment = '') {
    $cart_item = entity_create(
      'cart_item',
      array(
        'cbid' => $cbid,
        'entity_type' => $entity_type,
        'entity_id' => $entity_id,
        'entity_title' => $entity_title,
        'context_url' => $context_url,
        'context_comment' => $context_comment,
        'tjiid' => 0,
        'status' => self::STATUS_OPEN,
      )
    );
    $cart_item->save();

    return $cart_item;
  }

}
