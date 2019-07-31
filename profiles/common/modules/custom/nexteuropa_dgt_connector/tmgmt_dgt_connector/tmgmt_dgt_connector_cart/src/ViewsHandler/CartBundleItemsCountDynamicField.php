<?php

namespace Drupal\tmgmt_dgt_connector_cart\ViewsHandler;

use Drupal\tmgmt_dgt_connector_cart\Entity\CartBundle;
use views_handler_field;

/**
 * Custom Views field handler to present a target languages field.
 */
class CartBundleItemsCountDynamicField extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    // Get related CartItems entities.
    $cbid = $this->get_value($values);
    $cart_items = CartBundle::getActiveCartItems($cbid);
    $char_count = 0;
    /** @var \Drupal\tmgmt_dgt_connector_cart\Entity\CartItem $cart_item */
    foreach ($cart_items as $cart_item) {
      $char_count += $cart_item->getCharCount();
    }

    return $char_count;
  }

}
