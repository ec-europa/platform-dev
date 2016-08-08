<?php

/**
 * @file
 * Provides admin forms for map layer entities.
 */

/**
 * Handles submit creating and editing map layer_type.
 */
function ec_mapeditor_layer_type_form_submit(&$form, &$form_state) {
  $map_layer_type = entity_ui_form_submit_build_entity($form, $form_state);

  // Saves and goes back.
  ec_mapeditor_layer_type_save($map_layer_type);

  // Redirects user back to list of map layer types.
  $form_state['redirect'] = 'admin/structure/map-layer-types';
}

/**
 * Redirects to the deletion confirmation form.
 */
function ec_mapeditor_layer_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/map-layer-types/' . $form_state['map_layer_type']->type . '/delete';
}

/**
 * Defines map layer type deletion form.
 */
function ec_mapeditor_layer_type_form_delete_confirm($form, &$form_state, $map_layer_type) {
  $form_state['map_layer_type'] = $map_layer_type;

  // Always provide entity id in the same form key as in the entity edit form.
  $form['map_layer_type_id'] = array(
    '#type' => 'value',
    '#value' => entity_id('map_layer_type', $map_layer_type),
  );
  return confirm_form($form,
    t('Are you sure you want to delete map_layer type %title?', array('%title' => entity_label('map_layer_type', $map_layer_type))),
    'map_layer/' . entity_id('map_layer_type', $map_layer_type),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Handles map layer type deletion form submission.
 */
function ec_mapeditor_layer_type_form_delete_confirm_submit($form, &$form_state) {
  $map_layer_type = $form_state['map_layer_type'];
  ec_mapeditor_layer_type_delete($map_layer_type);
  watchdog('ec_mapeditor_layer', '@type: deleted %title.', array(
    '@type' => $map_layer_type->type,
    '%title' => $map_layer_type->label,
  ));
  drupal_set_message(t('@type %title has been deleted.', array(
    '@type' => $map_layer_type->type,
    '%title' => $map_layer_type->label,
  )));

  $form_state['redirect'] = 'admin/structure/map-layer-types';
}

/**
 * Provides page to select map layer type to add new map layer.
 */
function ec_mapeditor_layer_admin_add_page() {
  $items = array();
  foreach (ec_mapeditor_layer_types() as $map_layer_type_key => $map_layer_type) {
    $items[] = l(entity_label('map_layer_type', $map_layer_type), 'admin/structure/map-layer/add/' . $map_layer_type_key);
  }
  return array(
    'list' => array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#title' => t('Select type of map layer to create.'),
    ),
  );
}

/**
 * Add new map layer page callback.
 */
function ec_mapeditor_layer_add($type) {
  $map_layer_type = ec_mapeditor_layer_types($type);
  $map_layer = entity_create('map_layer', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('map_layer_type', $map_layer_type))));
  $output = drupal_get_form('map_layer_form', $map_layer);
  return $output;
}

/**
 * Handles map layer form submission.
 */
function ec_mapeditor_layer_form_submit($form, &$form_state) {
  $map_layer = $form_state['map_layer'];

  // Copies submitted values to entity properties for simple entity forms.
  entity_form_submit_build_entity('map_layer', $map_layer, $form, $form_state);

  // Sets the generic layer settings.
  $settings['control'] = $form_state['values']['control'];
  $settings['show_settings'] = $form_state['values']['show_settings'];

  // Adds values of custom field the settings.
  $settings = _ec_mapeditor_layer_save_settings($settings, $form_state);

  // Formats settings in json.
  $map_layer->settings = json_encode($settings);

  // Saves the map.
  ec_mapeditor_layer_save($map_layer);

  // Displays the saved map layer.
  $map_layer_uri = entity_uri('map_layer', $map_layer);
  $form_state['redirect'] = $map_layer_uri['path'];
  drupal_set_message(t('Map layer %title saved.', array('%title' => entity_label('map_layer', $map_layer))));
}

/**
 * Loads deletion confirmation form.
 */
function ec_mapeditor_layer_form_submit_delete($form, &$form_state) {
  $map_layer = $form_state['map_layer'];
  $map_layer_uri = entity_uri('map_layer', $map_layer);
  $form_state['redirect'] = $map_layer_uri['path'] . '/delete';
}

/**
 * Defines deletion confirmation form.
 */
function ec_mapeditor_layer_delete_form($form, &$form_state, $map_layer) {
  $form_state['map_layer'] = $map_layer;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['map_layer_type_id'] = array(
    '#type' => 'value',
    '#value' => entity_id('map_layer', $map_layer),
  );
  $map_layer_uri = entity_uri('map_layer', $map_layer);
  return confirm_form($form,
    t('Are you sure you want to delete map layer %title?', array('%title' => entity_label('map_layer', $map_layer))),
    $map_layer_uri['path'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Handles deletion form submission.
 */
function ec_mapeditor_layer_delete_form_submit($form, &$form_state) {
  $map_layer = $form_state['map_layer'];
  ec_mapeditor_layer_delete($map_layer);
  drupal_set_message(t('Map layer %title deleted.', array('%title' => entity_label('map_layer', $map_layer))));
  $form_state['redirect'] = '<front>';
}
