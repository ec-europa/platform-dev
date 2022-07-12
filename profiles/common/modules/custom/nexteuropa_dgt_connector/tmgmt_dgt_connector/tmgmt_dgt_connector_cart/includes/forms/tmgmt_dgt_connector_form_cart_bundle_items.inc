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

  // @todo: Implement a proper theme function to get rid of the markup.
  $details_list = array(
    '<strong>ID: </strong>' . $cbid,
    '<strong>Target languages: </strong>' . drupal_strtoupper($cart_bundle->target_languages),
    '<strong>Created: </strong>' . format_date($cart_bundle->created, 'custom', 'd/m/Y G:i:s'),
    '<strong>Changed: </strong>' . format_date($cart_bundle->changed, 'custom', 'd/m/Y G:i:s'),
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
    'entity_title' => t('Bundle item'),
    'entity_type' => t('Item type'),
    'char_count' => t('Character count'),
    'context_url' => t('Context URL'),
    'context_comment' => t('Context comment'),
  );

  $options = array();
  /** @var \Drupal\tmgmt_dgt_connector_cart\Entity\CartItem $item */
  foreach ($cart_items as $item) {
    $options[$item->ciid] = array(
      'entity_title' => $item->entity_title,
      'entity_type' => $item->entity_type,
      'char_count' => $item->getCharCount(),
      'context_url' => array(
        'data' => array(
          '#type' => 'textfield',
          '#value' => $item->context_url,
          '#size' => 60,
          '#disabled' => TRUE,
          '#name' => "cart_items_fields[$item->ciid][context_url]",
          '#attributes' => array('placeholder' => t('Insert URL')),
        ),
      ),
      'context_comment' => array(
        'data' => array(
          '#type' => 'textarea',
          '#value' => empty($item->context_comment) ? '' : $item->context_comment,
          '#size' => 10,
          '#disabled' => TRUE,
          '#name' => "cart_items_fields[$item->ciid][context_comment]",
          '#attributes' => array('placeholder' => t('Insert comment')),
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
    '#value' => $cart_items,
  );

  $form['submit_changes'] = array(
    '#type' => 'submit',
    '#value' => 'Submit changes',
    '#submit' => array('tmgmt_dgt_connector_form_cart_items_fields_submit'),
  );

  $form['submit_discard'] = array(
    '#type' => 'submit',
    '#value' => 'Discard selected items',
    '#submit' => array('tmgmt_dgt_connector_form_cart_items_discard_submit'),
  );

  // Form validation:
  $form['#validate'] = array('tmgmt_dgt_connector_form_cart_custom_validation');

  return $form;
}

/**
 * Custom form validation handler.
 */
function tmgmt_dgt_connector_form_cart_custom_validation($form, &$form_state) {
  switch ($form_state['values']['op']) {
    // Custom validation for submissions of exposed fields.
    case TMGMT_DGT_CONNECTOR_CART_SUBMIT_CHANGES:
      // @todo: Implement the 'url' and 'comment' validations.
      if (!isset($form_state['values']['cart_items_fields'])
        || empty($form_state['values']['cart_items_fields'])) {
        form_set_error('form[cart_items_selected', t('No items found.'));
      }
      break;

    // Custom validation for discarding selected items.
    case TMGMT_DGT_CONNECTOR_CART_SUBMIT_DISCARD:
      if (empty(_tmgmt_dgt_connector_cart_get_selected_cart_items($form_state))) {
        form_set_error('form[cart_items_selected', t('Please select item/s to perform an action.'));
      }
      break;
  }
}

/**
 * Custom form submit handler for saving editable fields values.
 */
function tmgmt_dgt_connector_form_cart_items_fields_submit($form, &$form_state) {
  // Updating CartItem entities properties.
  _tmgmt_dgt_connector_cart_update_cart_items($form_state);

  // Updating the CartBundle entity properties.
  _tmgmt_dgt_connector_cart_update_cart_bundle($form_state);

  // Displaying confirmation message.
  _tmgmt_dgt_connector_cart_display_message($form_state);

  // Refreshing the form.
  $form_state['rebuild'] = TRUE;

  // Preventing of running the reload function if the ajax context is not set.
  if (isset($form_state['ajax']) && $form_state['ajax']) {
    ctools_ajax_command_reload();
  }
}

/**
 * Custom form submit handler for discarding cart items.
 */
function tmgmt_dgt_connector_form_cart_items_discard_submit($form, &$form_state) {
  // Getting selected values from the form submission.
  $selected_items = _tmgmt_dgt_connector_cart_get_selected_cart_items($form_state);
  // Loading the selected CartItems entities.
  $cart_items = entity_load('cart_item', $selected_items);

  // Setting up the status for each of the CartItem entity.
  foreach ($cart_items as $cart_item) {
    $cart_item->status = CartItem::STATUS_DISCARDED;
    $cart_item->save();
  }

  // Updating the change date value of a CartBundle entity.
  _tmgmt_dgt_connector_cart_update_cart_bundle($form_state);

  // Displaying the message.
  _tmgmt_dgt_connector_cart_display_message($form_state);

  // Refreshing the form.
  if (empty($form_state['redirect'])) {
    $form_state['rebuild'] = TRUE;
  }

  // Prevent running reload function if we are out of the ajax context.
  if (isset($form_state['ajax']) && $form_state['ajax']) {
    ctools_ajax_command_reload();
  }
}

/**
 * Updates the CartBundle entity properties.
 *
 * @param array $form_state
 *   The form state array.
 */
function _tmgmt_dgt_connector_cart_update_cart_bundle(array &$form_state) {
  // Loading the CartBundle entity.
  $cbid = $form_state['build_info']['args']['cbid'];
  $cart_bundle = entity_load_single('cart_bundle', $cbid);

  // Updating the change date of a CartBundle entity.
  $cart_bundle->save();

  // Discard the CartBundle entity if needed and close the popup.
  if (_tmgmt_dgt_connector_cart_discard_cart_bundle($form_state, $cart_bundle)) {
    $form_state['redirect'] = TMGMT_DGT_CONNECTOR_CART_VIEW_PATH;
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] = ctools_ajax_command_redirect(TMGMT_DGT_CONNECTOR_CART_VIEW_PATH);
  }
}

/**
 * Updates CartItem entities properties.
 *
 * @param array $form_state
 *   The form state array.
 */
function _tmgmt_dgt_connector_cart_update_cart_items(array &$form_state) {
  // Getting the CartItems IDs.
  $ids = array_keys($form_state['values']['cart_items_fields']);
  $fields = $form_state['values']['cart_items_fields'];
  $cart_items = entity_load('cart_item', $ids);

  // Iterating through the CartItem entities and setting their properties.
  foreach ($cart_items as $id => $cart_item) {
    foreach ($fields[$id] as $field => $value) {
      $cart_item->{$field} = !is_array($value) ? check_plain($value) : $value;
    }
    $cart_item->save();
  }
}

/**
 * Discards selected CartItems and a CartBundle if needed.
 *
 * @param array $form_state
 *   The form state array.
 * @param \Drupal\tmgmt_dgt_connector_cart\Entity\CartBundle $cart_bundle
 *   The CartBundle entity.
 *
 * @return bool
 *   Returns TRUE if the CartBundle entity was discarded else FALSE.
 */
function _tmgmt_dgt_connector_cart_discard_cart_bundle(array &$form_state, CartBundle $cart_bundle) {
  if ($form_state['values']['op'] == TMGMT_DGT_CONNECTOR_CART_SUBMIT_DISCARD) {
    $selected_items = _tmgmt_dgt_connector_cart_get_selected_cart_items($form_state);
    if ($selected_items == $form_state['values']['cart_items_selected']) {
      $cart_bundle->status = CartBundle::STATUS_DISCARDED;
      $cart_bundle->save();

      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Returns selected CartItem IDs based on the form state.
 *
 * @param array $form_state
 *   The form state array.
 *
 * @return array
 *   An array with IDs of selected CartItems entities.
 */
function _tmgmt_dgt_connector_cart_get_selected_cart_items(array &$form_state) {
  return array_filter($form_state['values']['cart_items_selected']);
}

/**
 * Provides messages for submitted actions.
 *
 * @param array $form_state
 *   The form state array.
 */
function _tmgmt_dgt_connector_cart_display_message(array &$form_state) {
  switch ($form_state['values']['op']) {
    // Messages for submissions of exposed fields.
    case TMGMT_DGT_CONNECTOR_CART_SUBMIT_CHANGES:
      $message = t('Your changes have been successfully submitted.');
      break;

    // Messages for discarding selected items.
    case TMGMT_DGT_CONNECTOR_CART_SUBMIT_DISCARD:
      $message = t('Selected translatable items were discarded.');
      break;
  }

  if (isset($message)) {
    drupal_set_message($message);
  }
}
