<?php

namespace Drupal\tmgmt_dgt_connector_cart\ViewsHandler;

use views_handler_field;

/**
 * Custom Views field handler to present a target languages field.
 */
class CartBundleItemsField extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function render($values) {

    $cbid = $this->get_value($values);
    $view = views_get_view('bundle_items');
    $view->set_display('master');
    $view->pre_execute(array($cbid));
    $view->execute();
    return $view->render();

  }

}
