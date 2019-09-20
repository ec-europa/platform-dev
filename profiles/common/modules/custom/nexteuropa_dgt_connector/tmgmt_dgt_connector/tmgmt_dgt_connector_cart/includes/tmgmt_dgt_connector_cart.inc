<?php

/**
 * @file
 * Include file with helper functions for TMGMT DGT connector cart.
 */

use Drupal\tmgmt_dgt_connector_cart\Entity\CartItem;

/**
 * Helper function to get the CartItem entities based on a Job Items list.
 *
 * @param array $job_items
 *   Array with Job Items.
 *
 * @return array
 *   An array of CartItem entity objects indexed by their IDs.
 */
function _tmgmt_dgt_connector_cart_get_items_by_jobitems(array $job_items) {
  return CartItem::loadWithProperties(array('tjiid' => $job_items));
}
