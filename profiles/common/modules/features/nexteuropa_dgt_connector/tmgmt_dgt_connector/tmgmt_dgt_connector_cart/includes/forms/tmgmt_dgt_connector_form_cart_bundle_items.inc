<?php

/**
 * @file
 * CartItems entities management form definition.
 */

/**
 * Custom form callback - List of CartItems entities for a given CartBundle.
 */
function tmgmt_dgt_connector_form_cart_bundle_items($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Placeholder'),
  );

  return $form;
}
