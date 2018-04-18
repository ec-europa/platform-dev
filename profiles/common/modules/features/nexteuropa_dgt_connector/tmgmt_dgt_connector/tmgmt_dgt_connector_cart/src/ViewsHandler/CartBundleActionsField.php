<?php

namespace Drupal\tmgmt_dgt_connector_cart\ViewsHandler;

use views_handler_field;

/**
 * Custom Views field handler to present a target languages field.
 */
class CartBundleActionsField extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    ctools_include('modal');
    ctools_modal_add_js();
    $cbid = $this->get_value($values);

    $send_link = l(
      t('Send'),
      "admin/tmgmt/dgt_cart/items-send/$cbid",
      array()
    );

    $edit_link = l(
      t('Edit'),
      "admin/tmgmt/dgt_cart/items-edit/$cbid/nojs",
      array(
        'attributes' => array(
          'class' => 'ctools-use-modal',
        ),
      )
    );

    $discard_link = l(
      t('Discard'),
      "admin/tmgmt/dgt_cart/items-discard/$cbid/nojs",
      array('query' => drupal_get_destination())
    );

    return $send_link . ' ' . $edit_link . ' ' . $discard_link;
  }

}
