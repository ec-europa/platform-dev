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
    $link_text = 'edit';
    return l(
      $link_text,
      "admin/dgt_connector/cart-items-wrapper/$cbid/nojs",
      array(
        'attributes' => array(
          'class' => 'ctools-use-modal',
        ),
      )
    );
  }

}
