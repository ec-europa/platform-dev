<?php

namespace Drupal\tmgmt_dgt_connector_cart\ViewsHandler;

use views_handler_field;

/**
 * Custom Views field handler to present a target languages field.
 */
class CartBundleItemsFormLinkDynamicField extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    ctools_include('modal');
    ctools_modal_add_js();
    $cbid = $this->get_value($values);
    $edit_link = l(
      t('Edit'),
      "admin/dgt_connector/cart-items-edit/$cbid/nojs",
      array(
        'attributes' => array(
          'class' => 'ctools-use-modal',
        ),
      )
    );
    $send_link = l(
      t('Send'),
      "admin/dgt_connector/cart-items-send/$cbid",
      array()
    );
    $discard_link = l(
      t('Discard'),
      "admin/dgt_connector/cart-items-discard/$cbid/nojs",
      array('query' => drupal_get_destination())
    );
    return $edit_link . ' ' . $send_link . ' ' . $discard_link;
  }

}
