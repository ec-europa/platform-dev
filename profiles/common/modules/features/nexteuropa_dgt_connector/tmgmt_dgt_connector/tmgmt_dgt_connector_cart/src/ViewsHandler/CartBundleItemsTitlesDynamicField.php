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
    $header = array(t('Item Title'), t('Item Type'));
    $rows = array();
    /** @var \Drupal\tmgmt_dgt_connector_cart\Entity\CartItem $cart_item */
    foreach ($cart_items as $cart_item) {
      $rows[] = array($cart_item->entity_title, $cart_item->entity_type);
    }

    return theme('table', array('header' => $header, 'rows' => $rows));
  }

}
