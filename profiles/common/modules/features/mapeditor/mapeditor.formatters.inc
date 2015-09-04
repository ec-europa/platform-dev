<?php

/**
 * @file
 * Mapeditor field formatter functions.
 */

/**
 * Implements hook_field_formatter_info().
 */
function mapeditor_field_formatter_info() {
  $formatters = array();
  if (module_exists('geofield')) {
    $map_defaults = _mapeditor_map_defaults();
    $map = $map_defaults['map'];
    $settings = $map_defaults['settings'];
    $formatters['mapeditor_map'] = array(
      'label' => t('European Commission map'),
      'field types' => array('geofield'),
      'settings' => array(
        'tile_layer' => $map['map'],
        'height' => $settings['height'],
        'zoom' => $map['zoom'],
        'icon' => $settings['icon'],
        'center' => $map['center'],
        'attribution' => NULL,
      ),
    );
  }
  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function mapeditor_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();
  if ($display['type'] == 'mapeditor_map') {
    $element['tile_layer'] = _mapeditor_form_elements('tile_layer', $settings);
    $element['height'] = _mapeditor_form_elements('height', $settings);
    $element['zoom'] = _mapeditor_form_elements('zoom', $settings);
    $element['icon'] = _mapeditor_form_elements('icon', $settings);
    $element['center'] = _mapeditor_form_elements('center', $settings);
    $element['attribution'] = _mapeditor_form_elements('attribution', $settings);
  }
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function mapeditor_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = '';
  if ($display['type'] == 'mapeditor_map') {
    $summary = t('@height px, @map, @icon', array(
      '@height' => $settings['height']['height'],
      '@map' => $settings['tile_layer']['tile_layer'],
      '@icon' => $settings['icon']['icon'],
    ));
  }
  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function mapeditor_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $field_settings = $display['settings'];
  if (count($items) == 0) {
    return '';
  }
  else {
    switch ($display['type']) {
      case 'mapeditor_map':

        // Fetches map default definition and settings.
        $map_defaults = _mapeditor_map_defaults();
        $map = $map_defaults['map'];
        $settings = $map_defaults['settings'];

        // Disables popup for the field formatter because there is no way to
        // store pop up information in the geofield.
        $settings['popup'] = FALSE;
        $settings['popin'] = FALSE;
        $settings['show_popup'] = FALSE;

        // Returns geojson formatted geofield data. Uses same approach as
        // mapeditor map content type and view. _mapeditor_prepare_features
        // expects multiple items that hold multiple features.
        $field_items = array(
          array(
            'field_items' => $items,
          ),
        );
        $features = _mapeditor_prepare_features($field_items);
        if (isset($field_settings['center']['lat']) && isset($field_settings['center']['lon'])) {
          $map['center'] = array(
            $field_settings['center']['lat'],
            $field_settings['center']['lon'],
          );
        }
        $map['zoom'] = $field_settings['zoom']['initialZoom'];
        $map['map'] = $field_settings['tile_layer']['tile_layer'];
        $settings['height'] = $field_settings['height']['height'];
        $settings['icon'] = $field_settings['icon']['icon'];
        if (isset($field_settings['center']['fitbounds'])) {
          $settings['fitbounds'] = $field_settings['center']['fitbounds'];
        }
        $map['attributionControl'] = $field_settings['attribution']['attributionControl'];
        $map['attribution'] = $field_settings['attribution']['attribution'];

        // Builds the map.
        $mapeditor_map = new MapeditorMapBuild($map, $settings);
        $mapeditor_map->setCustomJs('map.js');
        $mapeditor_map->setFeatures($features);
        $element[0] = $mapeditor_map->build;
        break;
    }
    return $element;
  }
}
