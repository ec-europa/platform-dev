<?php

/**
 * @file
 * Documentation for EC mapeditor API.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Declares a map layer.
 *
 * Registers the map layer sub module. Defines the name of the map layer type,
 * which custom form elements it wants to add to the map and a custom
 * JavaScript that can be passed to the Webtools map. The form elements can be
 * defined by EC mapeditor layer or other custom layer modules by
 * implementing hook_map_form_elements().
 */
function hook_layer_info() {
  return array(
    'user_layer' => array(
      'form_elements' => array(
        'popup',
        'clustering',
        'icon',
        'attribution',
        'user_picture_icon',
      ),
      'custom_js' => base_path() . drupal_get_path('module', 'user_layer') . "/js/user_layer.js?v=" . rand(0, 33333),
    ),
  );
}

/**
 * Declares additional form elements for the map layer form.
 *
 * Defines custom map layer form elements for a custom map layer. These elements
 * are added to the form via hook_layer_info().
 */
function hook_map_form_elements() {
  $form_elements = array();

  // Defines is username is shown when hovering a marker on the map.
  $form_elements['user_picture_icon'] = array(
    '#type' => 'container',
    '#weight' => 15,
    'use_user_picture_icon' => array(
      '#type' => 'checkbox',
      '#title' => t('Use the user icture as marker icon on the map'),
    ),
    'image_style' => array(
      '#type' => 'select',
      '#options' => _user_layer_get_image_styles(),
      '#title' => t('Image style for the user picture marker icon'),
    ),
  );
  return $form_elements;
}

/**
 * Alters to content of a map layer.
 *
 * Lets map layer sub modules changes the content of the map layer. For
 * example for adding the map features.
 */
function hook_layer_content_alter(&$content, $wrapper, $entity) {

  // Fetches map data from user layer.
  if ($entity->type == 'user_layer') {
    $settings = drupal_json_decode($wrapper->settings->value());
    $users = _user_layer_fetch_users();
    if ($users) {
      $layers[] = array(
        'layer_settings' => $settings,
        'label' => $wrapper->title->value(),
        'users' => $users,
        'id' => _ec_mapeditor_layer_id($wrapper->title->value()),
      );
      $content['#attached']['js'][] = array(
        'data' => array(
          'user_layers' => $layers,
        ),
        'type' => 'setting',
      );
      return $content;
    }
  }
}

/**
 * Alters the map layer settings.
 *
 * Allows custom map layer modules to change the map layer settings. It can be
 * used for example to add more settings to the map layer settings. These
 * settings are saved when submitting the map layer via an inline entity form.
 * See MapLayerInlineEntityFormController->entityFormSubmit().
 */
function hook_map_layer_settings_alter(&$settings, $map_layer) {
  if ($map_layer->type == 'user_layer') {
    $settings['user_picture_icon'] = $map_layer->user_picture_icon;
  }
  return $settings;
}

/**
 * Alters the map layer settings.
 *
 * Allows custom map layer modules to change the map layer settings. It can be
 * used for example to add more settings to the map layer settings. These
 * settings are saved when submitting the map layer via a stand alone form. See
 * ec_mapeditor_layer_form_submit().
 */
function hook_stand_alone_map_layer_settings_alter(&$settings, $form_state) {
  if ($form_state['map_layer']->type == 'user_layer') {
    $values = $form_state['values'];
    $settings['user_picture_icon'] = $values['user_picture_icon'];
  }
  return $settings;
}

/**
 * @} End of "addtogroup hooks".
 */
