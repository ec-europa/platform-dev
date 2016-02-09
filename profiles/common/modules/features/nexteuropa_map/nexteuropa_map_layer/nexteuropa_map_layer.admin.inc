<?php

/**
 * @file
 * Provides admin forms for map layer entities.
 */

/**
 * Generates the map layer type editing form.
 *
 * @todo find out how to rename to nexteuropa_map_layer_type_form().
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
      'exists' => 'nexteuropa_map_layer_types',
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
      '#submit' => array('nexteuropa_map_layer_type_form_submit_delete'),
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
  nexteuropa_map_layer_type_save($map_layer_type);

  // Redirect user back to list of map layer types.
  $form_state['redirect'] = 'admin/structure/map-layer-types';
}

/**
 * Redirects to the deletion confirmation form.
 */
function nexteuropa_map_layer_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/map-layer-types/' . $form_state['map_layer_type']->type . '/delete';
}

/**
 * Map layer type delete form.
 */
function nexteuropa_map_layer_type_form_delete_confirm($form, &$form_state, $map_layer_type) {
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
 * Map layer type delete form submit handler.
 */
function nexteuropa_map_layer_type_form_delete_confirm_submit($form, &$form_state) {
  $map_layer_type = $form_state['map_layer_type'];
  nexteuropa_map_layer_type_delete($map_layer_type);
  watchdog('map_layer_type', '@type: deleted %title.', array(
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
 * Page to select map layer type to add new map layer.
 */
function nexteuropa_map_layer_admin_add_page() {
  $items = array();
  foreach (nexteuropa_map_layer_types() as $map_layer_type_key => $map_layer_type) {
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
function nexteuropa_map_layer_add($type) {
  $map_layer_type = nexteuropa_map_layer_types($type);
  $map_layer = entity_create('map_layer', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('map_layer_type', $map_layer_type))));
  $output = drupal_get_form('map_layer_form', $map_layer);
  return $output;
}

/**
 * Defines the stand alone map layer form.
 *
 * See also MapLayerInlineEntityFormController->entityForm().
 * @todo find out how to rename to nexteuropa_map_layer_form().
 */
function map_layer_form($form, &$form_state, $map_layer) {

  // Sets map_layer entity for the submit form.
  $form_state['map_layer'] = $map_layer;

  // Loads settings.
  $settings = new MapLayerSettings();
  if (!empty($map_layer->settings)) {
    $settings->customize(drupal_json_decode($map_layer->settings));
  }
  // @todo. figure out how to prevent this?
  $settings = $settings->settings;

  // Makes settings available in form alter hooks.
  $form_state['settings'] = $settings;

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
  // @todo. figure out what are map layer defaults.

  // Provides checkboxes to define how the layer is shown in the layer control.
  $form['control'] = nexteuropa_map_layer_form_elements('control', $settings);
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
    '#submit' => $submit + array('nexteuropa_map_layer_form_submit'),
  );

  // Show Delete button if we edit map layer.
  $map_layer_id = entity_id('map_layer', $map_layer);
  if (!empty($map_layer_id) && nexteuropa_map_layer_access('edit', $map_layer)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('nexteuropa_map_layer_form_submit_delete'),
    );
  }
  $form['#validate'][] = 'nexteuropa_map_layer_form_validate';
  return $form;
}

/**
 * Validates map layer form submission.
 */
function nexteuropa_map_layer_form_validate($form, &$form_state) {
}

/**
 * Map layer submit handler.
 */
function nexteuropa_map_layer_form_submit($form, &$form_state) {

  dpm($form_state['values']);

  $map_layer = $form_state['map_layer'];

  // Copies submitted values to entity properties for simple entity forms.
  entity_form_submit_build_entity('map_layer', $map_layer, $form, $form_state);

  // Constructs the layer settings for simple json storage in text field.
  $settings = array(
    'control' => array(
      'show_in_control' => $form_state['values']['show_in_control'],
      'enabled' => $form_state['values']['enabled'],
    ),
    'show_settings' => $form_state['values']['show_settings'],
  );

  // Allows modules to alter the map_layer settings.
  drupal_alter('map_layer_settings', $settings, $map_layer);

  // Stores settings in json.
  $map_layer->settings = json_encode($settings);

  // Saves the map.
  nexteuropa_map_layer_save($map_layer);

  // Shows the created entity.
  $map_layer_uri = entity_uri('map_layer', $map_layer);
  $form_state['redirect'] = $map_layer_uri['path'];
  drupal_set_message(t('Map layer %title saved.', array('%title' => entity_label('map_layer', $map_layer))));
}

/**
 * Loads deletion confirmation form.
 */
function nexteuropa_map_layer_form_submit_delete($form, &$form_state) {
  $map_layer = $form_state['map_layer'];
  $map_layer_uri = entity_uri('map_layer', $map_layer);
  $form_state['redirect'] = $map_layer_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function nexteuropa_map_layer_delete_form($form, &$form_state, $map_layer) {
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
 * Delete form submit handler.
 */
function nexteuropa_map_layer_delete_form_submit($form, &$form_state) {
  $map_layer = $form_state['map_layer'];
  nexteuropa_map_layer_delete($map_layer);
  drupal_set_message(t('Map layer %title deleted.', array('%title' => entity_label('map_layer', $map_layer))));
  $form_state['redirect'] = '<front>';
}
