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
 * Constructs the map form.
 */
function map_form($form, &$form_state, $map) {
  $form_state['map'] = $map;

  // Provides a title field.
  $form['title'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Name'),
    '#default_value' => $map->title,
  );

  // Provides a description field.
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $map->description,
  );

  // Stores the user ID.
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $map->uid,
  );

  // Provides a field to store various map settings.
  $settings = new MapSettings();
  if (!empty($map->settings)) {
    $settings->customize(drupal_json_decode($map->settings));
  }

  // @todo. how to prevent this?
  $settings = $settings->settings;

  // Provides a checkbox to show /hide settings field.
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
    '#default_value' => isset($map->settings) ? $map->settings : '',
    '#description' => t('Settings (json encoded)'),
    '#states' => array(
      'visible' => array(
        ':input[name="show_settings"]' => array('checked' => TRUE),
      ),
    ),
  );

  // Adds field UI fields.
  field_attach_form('map', $map, $form, $form_state);

  // Adds common map form elements.
  $elements = array('height', 'center', 'zoom', 'tiles', 'attribution');
  $custom_form_elements = _ec_mapeditor_custom_map_form_elements($elements, $settings);
  $form += $custom_form_elements;

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }
  $form['actions'] = array(
    '#weight' => 100,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save map'),
    '#submit' => $submit + array('ec_mapeditor_form_submit'),
  );

  // Adds delete button when editing a map.
  $map_id = entity_id('map', $map);
  if (!empty($map_id) && ec_mapeditor_access('edit', $map)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ec_mapeditor_form_submit_delete'),
    );
  }
  return $form;
}
