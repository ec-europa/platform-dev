<?php

namespace Drupal\tmgmt_dgt_connector_cart\ViewsHandler;

use Drupal\tmgmt_dgt_connector_cart\Entity\CartBundle;
use views_handler_field;

/**
 * Custom Views field handler to present a target languages field.
 */
class CartBundleItemsTitlesDynamicField extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    // Get related CartItems entities.
    $cbid = $this->get_value($values);
    $cart_items = CartBundle::getActiveCartItems($cbid);
    $titles = array();
    /** @var \Drupal\tmgmt_dgt_connector_cart\Entity\CartItem $cart_item */
    foreach ($cart_items as $cart_item) {
      $titles[] = t('Type: <strong>%item_type</strong> | Title: <strong>%item_title</strong>', array(
        '%item_type' => $cart_item->entity_type,
        '%item_title' => $cart_item->entity_title,
      ));
    }

    return theme('item_list', array('items' => $titles));
  }

}
