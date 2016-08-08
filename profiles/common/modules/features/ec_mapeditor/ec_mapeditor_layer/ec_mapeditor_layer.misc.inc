<?php
/**
 * @file
 * Contains code with function names that do not comply with standards.
 *
 * Functions in this file could not be renamed at the moment of quality
 * assurance review without breaking the module. They cannot be renamed because
 * Drupal expects specific naming when dealing with entities. As discussed in
 * https://webgate.ec.europa.eu/fpfis/wikis/x/AjjCBw .
 */

/**
 * Generates the map layer type editing form.
 *
 * @todo find out how to rename to ec_mapeditor_layer_type_form().
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
      'exists' => 'ec_mapeditor_layer_types',
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
    '#submit' => array('ec_mapeditor_layer_type_form_submit'),
  );

  if (!$map_layer_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete map layer type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('ec_mapeditor_layer_type_form_submit_delete'),
    );
  }
  return $form;
}

/**
 * Defines the stand alone map layer form.
 *
 * See also MapLayerInlineEntityFormController->entityForm().
 *
 * @todo find out how to rename to ec_mapeditor_layer_form().
 */
function map_layer_form($form, &$form_state, $map_layer) {

  $form['#tree'] = TRUE;

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
  $control_form_element = _ec_mapeditor_custom_map_form_elements(array('control'), $settings);
  $form += $control_form_element;
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

  // Adds custom form elements from field API fields.
  field_attach_form('map_layer', $map_layer, $form, $form_state);

  // Adds custom form elements defined by the active map layer sub module.
  $type = $map_layer->type;
  $map_layers = module_invoke_all('layer_info');
  if (isset($map_layers[$type])) {
    $elements = $map_layers[$type]['form_elements'];
    $custom_form_elements = _ec_mapeditor_custom_map_form_elements($elements, $settings);
    $form += $custom_form_elements;
  }

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
    '#submit' => $submit + array('ec_mapeditor_layer_form_submit'),
  );

  // Shows delete button if we edit map layer.
  $map_layer_id = entity_id('map_layer', $map_layer);
  if (!empty($map_layer_id) && ec_mapeditor_layer_access('edit', $map_layer)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ec_mapeditor_layer_form_submit_delete'),
    );
  }

  // Lets modules alter the form.
  drupal_alter('layer_form', $form, $settings, $type);
  return $form;
}

/**
 * Load a map layer.
 */
function map_layer_load($mlid, $reset = FALSE) {
  $map_layers = map_layer_load_multiple(array($mlid), array(), $reset);
  return reset($map_layers);
}

/**
 * Load multiple map layers based on certain conditions.
 */
function map_layer_load_multiple($mlids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('map_layer', $mlids, $conditions, $reset);
}

/**
 * Load map layer type.
 */
function map_layer_type_load($map_layer_type) {
  return ec_mapeditor_layer_types($map_layer_type);
}
