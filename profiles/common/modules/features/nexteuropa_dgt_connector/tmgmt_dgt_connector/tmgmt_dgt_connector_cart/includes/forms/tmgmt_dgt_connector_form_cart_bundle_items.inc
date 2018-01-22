<?php

/**
 * @file
 * CartItems entities management form definition.
 */

define('TMGMT_DGT_CONNECTOR_CART_SUBMIT_CHANGES', 'Submit changes');
define('TMGMT_DGT_CONNECTOR_CART_SUBMIT_DISCARD', 'Discard selected items');


use Drupal\tmgmt_dgt_connector_cart\Entity\CartBundle;
use Drupal\tmgmt_dgt_connector_cart\Entity\CartItem;

/**
 * Custom form callback - List of CartItems entities for a given CartBundle.
 */
function tmgmt_dgt_connector_form_cart_bundle_items($form, &$form_state) {
  $cbid = $form_state['build_info']['args']['cbid'];
  $cart_bundle = entity_load_single('cart_bundle', $cbid);

  $cart_items = CartBundle::getActiveCartItems($cbid);

  $details_list = array(
    '<strong>ID: </strong>' . $cbid,
    '<strong>Target languages: </strong>' . drupal_strtoupper($cart_bundle->target_languages),
    '<strong>Created: </strong>' . format_date($cart_bundle->created, 'custom', 'Y.m.d H:i'),
    '<strong>Changed: </strong>' . format_date($cart_bundle->changed, 'custom', 'Y.m.d H:i'),
  );

  // @todo: if accepted, wrap all strings in the t() function.
  $form['cart_bundle_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bundle details'),
  );

  $form['cart_bundle_details']['cart_bundle_details'] = array(
    '#type' => 'item',
    '#markup' => theme('item_list', array('items' => $details_list)),
  );

  $header = array(
    'ciid' => t('Item ID'),
    'entity_type' => t('Entity type'),
    'entity_id' => t('Entity ID'),
    'entity_title' => t('Title'),
    'status' => t('Status'),
    'context_url' => t('Context URL'),
    'context_comment' => t('Context comment'),
  );

  $options = array();
  /** @var \Drupal\tmgmt_dgt_connector_cart\Entity\CartItem $item */
  foreach ($cart_items as $item) {
    $options[$item->ciid] = array(
      'ciid' => $item->ciid,
      'entity_type' => $item->entity_type,
      'entity_id' => $item->entity_id,
      'entity_title' => $item->entity_title,
      'status' => $item->status,
      'context_url' => array(
        'data' => array(
          '#type' => 'textfield',
          '#value' => $item->context_url,
          '#size' => 60,
          '#disabled' => TRUE,
          '#name' => "cart_items_fields[$item->ciid][context_url]",
        ),
      ),
      'context_comment' => array(
        'data' => array(
          '#type' => 'textarea',
          '#value' => empty($item->context_comment) ? '' : $item->context_comment,
          '#size' => 10,
          '#disabled' => TRUE,
          '#name' => "cart_items_fields[$item->ciid][context_comment]",
        ),
      ),
    );
  }

  $form['cart_items_selected'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No items were found.'),
    '#tree' => TRUE,
  );

  $form['cart_items_fields'] = array(
    '#type' => 'value',
  );

  $form['submit_changes'] = array(
    '#type' => 'submit',
    '#value' => 'Submit changes',
    '#submit' => array('tmgmt_dgt_connector_form_cart_bundle_items_fields_submit'),
  );

  $form['submit_discard'] = array(
    '#type' => 'submit',
    '#value' => 'Discard selected items',
    '#submit' => array('tmgmt_dgt_connector_form_cart_bundle_items_discard_submit'),
  );

  // Form validation:
  $form['#validate'] = array('tmgmt_dgt_connector_form_cart_custom_validation');

  return $form;
}

/**
 * Custom form validation handler to check editable fields.
 */
function tmgmt_dgt_connector_form_cart_custom_validation($form, &$form_state) {
  switch ($form_state['values']['op']) {
    case TMGMT_DGT_CONNECTOR_CART_SUBMIT_CHANGES:
      // @todo: implement validation for submitting changes.
      break;

    case TMGMT_DGT_CONNECTOR_CART_SUBMIT_DISCARD:
      // @todo: implement validation for discarding CartItem entities.
      break;

  }
}

/**
 * Custom form submit handler for saving editable fields values.
 */
function tmgmt_dgt_connector_form_cart_bundle_items_fields_submit($form, &$form_state) {
  if (isset($form_state['values']['cart_items_fields'])
    && !empty($form_state['values']['cart_items_fields'])) {
    // Getting the CartItems IDs.
    $ids = array_keys($form_state['values']['cart_items_fields']);
    $fields = $form_state['values']['cart_items_fields'];
    $cart_items = entity_load('cart_item', $ids);

    // Updating properties of CartItem entities.
    foreach ($cart_items as $id => $cart_item) {
      foreach ($fields[$id] as $field => $value) {
        $cart_item->{$field} = $value;
      }
      // This will also update the 'changed' property with a new timestamp.
      $cart_item->save();
    }

    // Updating the 'changed' property of a CartBundle entity.
    _tmgmt_dgt_connector_cart_update_cart_bundle_change_date($form_state['build_info']['args']['cbid']);

    // Refreshing the form.
    $form_state['rebuild'] = TRUE;
    ctools_ajax_command_reload();
  }
}

/**
 * Custom form submit handler for discarding cart items.
 */
function tmgmt_dgt_connector_form_cart_bundle_items_discard_submit($form, &$form_state) {
  if (isset($form_state['values']['cart_items_selected'])
    && !empty($form_state['values']['cart_items_selected'])) {
    // Getting selected values from the form submission.
    $selected_items = array_filter($form_state['values']['cart_items_selected'], function ($value) {
      return($value);
    });

    // Loading the selected CartItems entities.
    $cart_items = entity_load('cart_item', $selected_items);

    // Setting up the status for each of the CartItem entity.
    foreach ($cart_items as $cart_item) {
      $cart_item->status = CartItem::STATUS_DISCARDED;
      $cart_item->save();
    }

    if ($selected_items == $form_state['values']['cart_items_selected']) {
      // @todo: remove the CartBundle as the last CartItem was discarded.
    }
    // Updating the change date value of a CartBundle entity.
    _tmgmt_dgt_connector_cart_update_cart_bundle_change_date($form_state['build_info']['args']['cbid']);

    // Refreshing the form.
    $form_state['rebuild'] = TRUE;
    ctools_ajax_command_reload();
  }
}

/**
 * Helper function for updating the change date of a CartBundle entity.
 *
 * @param int $cbid
 *   The CartBundle ID.
 */
function _tmgmt_dgt_connector_cart_update_cart_bundle_change_date($cbid) {
  // Updating the change date of a CartBundle entity.
  $cart_bundle = entity_load_single('cart_bundle', $cbid);
  $cart_bundle->save();
}
