<?php

/**
 * @file
 * Extra view functionality for translation carts.
 */

/**
 * Implements hook_views_data_alter().
 */
function tmgmt_dgt_connector_cart_views_data_alter(&$data) {
  $data['cart_item']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    'cart_bundle' => array(
      // The primary key in the referenced table.
      'left_field' => 'cbid',
      // The foreign key in this table.
      'field' => 'cbid',
    ),
  );
}
