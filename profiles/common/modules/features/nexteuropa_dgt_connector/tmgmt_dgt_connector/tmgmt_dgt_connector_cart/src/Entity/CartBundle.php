<?php

namespace Drupal\tmgmt_dgt_connector_cart\Entity;

use Entity;
use EntityFieldQuery;

/**
 * DGT FTT Translator mapping entity.
 */
class CartBundle extends Entity {
  const STATUS_OPEN = 'OPEN';
  const STATUS_SENT = 'SENT';
  const STATUS_FINISHED = 'FINISHED';
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
   * Load a cart bundle entity from the database.
   *
   * @param int $cbid
   *   The CartBundle entity ID.
   * @param bool $reset
   *   Optional reset of the internal cache for the requested entity type.
   *
   * @return bool|CartBundle
   *   The CartBundle entity or FALSE if the entity was not found.
   */
  public static function load($cbid, $reset) {
    $cbids = isset($cbid) ? array($cbid) : array();
    $cart_bundle = self::loadMultiple($cbids, $reset);

    return $cart_bundle ? reset($cart_bundle) : FALSE;
  }

  /**
   * Load CartBundle entities from the database.
   *
   * @param array $cbids
   *   An array of CartBundle entities IDs.
   * @param bool $reset
   *   Optional reset of the internal cache for the requested entity type.
   *
   * @return array
   *   An array of CartBundle entity objects indexed by their ids or an empty
   *   array if no results are found.
   */
  public static function loadMultiple(array $cbids, $reset = FALSE) {
    return entity_load('cart_bundle', $cbids, array(), $reset);
  }

  /**
   * Load CartBundle entities filtered by a set of properties.
   *
   * @param array $properties
   *   An array with properties for querying for specific entities.
   *
   * @return array
   *   An array of CartBundle entity objects indexed by their IDs or an empty
   *   array if no results are found.
   */
  public static function loadWithProperties(array $properties) {
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
   * Create a CartBundle entity.
   *
   * @param int $uid
   *   An ID of the currently logged in user.
   * @param string $target_languages
   *   String with concatenated language prefixes.
   * @param string $status
   *   A cart bundle status.
   * @param int $tjid
   *   The TMGMTJob entity ID.
   *
   * @return bool
   *   A new instance of the CartBundle entity or FALSE.
   */
  public static function create($uid, $target_languages, $status = CartBundle::STATUS_OPEN, $tjid = 0) {
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

  /**
   * Gets the active CartItems entities by a given CartBundle ID.
   *
   * @param int $cbid
   *   The CartBundle ID.
   *
   * @return array
   *   An array of CartItems entity objects indexed by their IDs or an empty
   *   array if no results are found.
   */
  public static function getActiveCartItems($cbid) {
    $properties = array(
      'cbid' => $cbid,
      'status' => self::STATUS_OPEN,
    );

    return CartItem::loadWithProperties($properties);
  }

  /**
   * Get formatted array of target languages.
   *
   * @return array
   *   An array of target language codes.
   */
  public function getTargetLanguages() {
    return explode('.', $this->target_languages);
  }

  /**
   * Update status of the bundle.
   *
   * @param string $status
   *   The new status.
   */
  public function updateStatus($status) {
    $this->status = $status;
    $this->save();
  }

}
