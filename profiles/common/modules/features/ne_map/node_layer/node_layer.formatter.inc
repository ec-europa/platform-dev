<?php

/**
 * @file
 * Node field formatter functions.
 */

/**
 * Implements hook_field_formatter_info().
 */
function node_layer_field_formatter_info() {
  $formatters = array();
  if (module_exists('geofield')) {

    // Fetches default settings.
    $settings = new NEMapSettings();

    // @todo. how to prevent this?
    $settings = $settings->settings;

    // Defines settings available to this formatter.
    $formatters['ec_webtools_map'] = array(
      'label' => t('EC webtools map'),
      'field types' => array('geofield'),
      'settings' => array(
        'tiles' => $settings['tiles'],
        'height' => $settings['height'],
        'zoom' => $settings['zoom'],
        'icon' => $settings['icon'],
        'center' => $settings['center'],
        'attribution' => $settings['attribution'],
      ),
    );
  }
  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function node_layer_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  // Defnies formatter settings form by using shared form elements.
  if ($display['type'] == 'ec_webtools_map') {
    $element['tiles'] = ne_map_form_elements('tiles', $settings);
    $element['height'] = ne_map_form_elements('height', $settings);
    $element['zoom'] = ne_map_form_elements('zoom', $settings);
    $element['icon'] = map_layer_form_elements('icon', $settings);
    $element['center'] = ne_map_form_elements('center', $settings);
    $element['attribution'] = ne_map_form_elements('attribution', $settings);
  }
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function node_layer_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = '';
  if ($display['type'] == 'ec_webtools_map') {
    $summary = t('@height px, @map, @icon', array(
      '@height' => $settings['height']['height'],
      '@map' => $settings['tiles']['tiles'],
      '@icon' => $settings['icon']['icon'],
    ));
  }
  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function node_layer_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  if (count($items) == 0) {
    return '';
  }
  else {
    if ($display['type'] == 'ec_webtools_map') {
      $elements = array();

      // Fetches default settings.
      $settings = new NEMapSettings();

      // Apply custom field formatter settings.
      $settings->customize($display['settings']);

      // @todo. how to prevent this?
      $settings = $settings->settings;

      // Sets defaults that are irrelevant for the field formatter.
      $settings['clustering']['cluster_markers'] = FALSE;
      $settings['popup']['show_popup'] = FALSE;
      $settings['control']['enabled'] = TRUE;
      $settings['control']['show_in_control'] = FALSE;

      // Returns geojson formatted geofield data. Uses same approach as
      // map content type and view. _ne_map_prepare_features
      // expects multiple items that hold multiple features.
      $field_items = array(
        array(
          'field_items' => $items,
        ),
      );
      $features = node_layer_prepare_features($field_items);

      // Prepares layers to be attached as JavaScript setting.
      $layers[] = array(
        'layer_settings' => $settings,
        'label' => 'No label',
        'features' => $features,
        'id' => '123',
      );

      // Attaches layers as JavaScript setting.
      $elements['#attached']['js'][] = array(
        'data' => array(
          'node_layers' => $layers,
        ),
        'type' => 'setting',
      );

      // Creates the render array for the map.
      $map = new MapBuild($settings);

      // Defines the custom JavaScripts for the webtools JS map library.
      $map_layer_js = base_path() . drupal_get_path('module', 'map_layer') . "/js/map_layer.js?v=" . rand(0, 33333);
      $custom_js[] = $map_layer_js;
      $node_layer_js = base_path() . drupal_get_path('module', 'node_layer') . "/js/node_layer.js?v=" . rand(0, 33333);
      $custom_js[] = $node_layer_js;
      $ne_map_js = base_path() . drupal_get_path('module', 'ne_map') . "/js/ne_map.js?v=" . rand(0, 33333);
      $custom_js[] = $ne_map_js;
      $map->setMoreCustomJs($custom_js);
      $elements[0]['map'] = $map->build;
      return $elements;
    }
  }
}
