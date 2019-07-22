<?php

namespace Drupal\tmgmt_dgt_connector_cart\ViewsHandler;

use views_handler_field;

/**
 * Custom Views field handler to present a target languages field.
 */
class CartBundleLanguagesField extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function pre_render(&$values) {
    parent::pre_render($values);

    array_walk($values, function ($row) {
      $row->cart_bundle_target_languages = implode(', ', array_map('drupal_strtoupper', explode('.', $row->cart_bundle_target_languages)));
    });
  }

}
