<?php

/**
 * Generates the map layer type editing form.
 */
function map_layer_type_form($form, &$form_state, $map_layer_type, $op = 'edit') {

  if ($op == 'clone') {
    $map_layer_type->label .= ' (cloned)';
    $map_layer_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $map_layer_type->label,
    '#description' => t('The human-readable name of this map layer type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($map_layer_type->type) ? $map_layer_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $map_layer_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'map_layer_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this map layer type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($map_layer_type->description) ? $map_layer_type->description : '',
    '#description' => t('Description about the map layer type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save map layer type'),
    '#weight' => 40,
  );

  if (!$map_layer_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete map layer type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('map_layer_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing map layer_type.
 */
function map_layer_type_form_submit(&$form, &$form_state) {
  $map_layer_type = entity_ui_form_submit_build_entity($form, $form_state);

  // Save and go back.
  map_layer_type_save($map_layer_type);

  // Redirect user back to list of map layer types.
  $form_state['redirect'] = 'admin/structure/map-layer-types';
}

function map_layer_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/map-layer-types/' . $form_state['map_layer_type']->type . '/delete';
}

/**
 * Map layer type delete form.
 */
function map_layer_type_form_delete_confirm($form, &$form_state, $map_layer_type) {
  $form_state['map_layer_type'] = $map_layer_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['map_layer_type_id'] = array(
    '#type' => 'value',
    '#value' => entity_id('map_layer_type', $map_layer_type)
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
 * Map layer type delete form submit handler.
 */
function map_layer_type_form_delete_confirm_submit($form, &$form_state) {
  $map_layer_type = $form_state['map_layer_type'];
  map_layer_type_delete($map_layer_type);
  watchdog('map_layer_type', '@type: deleted %title.', array(
    '@type' => $map_layer_type->type,
    '%title' => $map_layer_type->label
  ));
  drupal_set_message(t('@type %title has been deleted.', array(
    '@type' => $map_layer_type->type,
    '%title' => $map_layer_type->label
  )));

  $form_state['redirect'] = 'admin/structure/map-layer-types';
}

/**
 * Page to select map layer type to add new map layer.
 */
function map_layer_admin_add_page() {
  $items = array();
  foreach (map_layer_types() as $map_layer_type_key => $map_layer_type) {
    $items[] = l(entity_label('map_layer_type', $map_layer_type), 'admin/structure/map-layer/add/' . $map_layer_type_key);
  }
  return array(
    'list' => array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#title' => t('Select type of map layer to create.')
    )
  );
}

/**
 * Add new map layer page callback.
 */
function map_layer_add($type) {
  $map_layer_type = map_layer_types($type);
  $map_layer = entity_create('map_layer', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('map_layer_type', $map_layer_type))));
  $output = drupal_get_form('map_layer_form', $map_layer);
  return $output;
}

/**
 * Map layer Form.
 */
function map_layer_form($form, &$form_state, $map_layer) {

  // Sets map_layer entity for the submit form.
  $form_state['map_layer'] = $map_layer;

  // Loads settings.
  $settings = new MapLayerSettings();
  if (!empty($map_layer->settings)) {
    $settings->customize(drupal_json_decode($map_layer->settings));
  }
  // @todo. how to prevent this?
  $settings = $settings->settings;

  $form['title'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Name'),
    '#default_value' => $map_layer->title,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#rows' => 2,
    '#default_value' => $map_layer->description,
  );
  $form['popup'] = map_layer_form_elements('popup', $settings);
  $form['clustering'] = map_layer_form_elements('clustering', $settings);
  $form['icon'] = map_layer_form_elements('icon', $settings);
  $form['enabled'] = map_layer_form_elements('enabled', $settings);
  $form['show_settings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show settings'),
    '#default_value' => $settings['show_settings'],
    '#weight' => 98,
  );
  $form['settings'] = array(
    '#weight' => 99,
    '#title' => t('Settings'),
    '#type' => 'textarea',
    '#default_value' => $map_layer->settings,
    '#description' => t('Settings (json encoded)'),
    '#states' => array(
      'visible' => array(
        ':input[name="show_settings"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $map_layer->uid,
  );

  field_attach_form('map_layer', $map_layer, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save map layer'),
    '#submit' => $submit + array('map_layer_form_submit'),
  );

  // Show Delete button if we edit map layer.
  $map_layer_id = entity_id('map_layer', $map_layer);
  if (!empty($map_layer_id) && map_layer_access('edit', $map_layer)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('map_layer_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'map_layer_form_validate';

  return $form;
}

function map_layer_form_validate($form, &$form_state) {

}

/**
 * Map layer submit handler.
 */
function map_layer_form_submit($form, &$form_state) {
  $map_layer = $form_state['map_layer'];

  entity_form_submit_build_entity('map_layer', $map_layer, $form, $form_state);

  map_layer_save($map_layer);

  $map_layer_uri = entity_uri('map_layer', $map_layer);

  $form_state['redirect'] = $map_layer_uri['path'];

  drupal_set_message(t('Map layer %title saved.', array('%title' => entity_label('map_layer', $map_layer))));
}

function map_layer_form_submit_delete($form, &$form_state) {
  $map_layer = $form_state['map_layer'];
  $map_layer_uri = entity_uri('map_layer', $map_layer);
  $form_state['redirect'] = $map_layer_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function map_layer_delete_form($form, &$form_state, $map_layer) {
  $form_state['map_layer'] = $map_layer;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['map_layer_type_id'] = array(
    '#type' => 'value',
    '#value' => entity_id('map_layer', $map_layer)
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
 * Delete form submit handler.
 */
function map_layer_delete_form_submit($form, &$form_state) {
  $map_layer = $form_state['map_layer'];
  map_layer_delete($map_layer);
  drupal_set_message(t('Map layer %title deleted.', array('%title' => entity_label('map_layer', $map_layer))));
  $form_state['redirect'] = '<front>';
}
