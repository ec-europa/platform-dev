<?php

/**
 * @file
 * Provides page content for Mapeditor module.
 */

/**
 * Provides an example of a webtools map.
 */
function _mapeditor_example_page() {

  // Fetches map default definition and settings.
  $map_defaults = _mapeditor_map_defaults();
  $map = $map_defaults['map'];
  $settings = $map_defaults['settings'];

  // Defines settings.
  $settings['height'] = 240;
  $settings['icon'] = 'blue';
  $settings['all_coordinates'] = array(
    array(51.5, -0.09),
    array(-5.91042, -51.16823),
  );

  // Defines map data (in geojson structure).
  $features = array(
    array(
      'type' => 'Feature',
      'properties' => array(
        'name' => 'Gunwalls',
        'popupContent' => 'Pops',
      ),
      'geometry' => array(
        'type' => 'Point',
        'coordinates' => array(-0.09, 51.5),
      ),
    ),
    array(
      'type' => 'Feature',
      'properties' => array(
        'name' => 'Gunwalls',
        'popupContent' => 'Pops',
      ),
      'geometry' => array(
        'type' => 'Point',
        'coordinates' => array(-51.16823, -5.91042),
      ),
    ),
  );

  // Builds the map.
  $mapeditor_map = new MapeditorMapBuild($map, $settings);
  $mapeditor_map->setCustomJs('map.js');
  $mapeditor_map->setFeatures($features);
  return $mapeditor_map->build;
}

/**
 * Provides an example of a webtools map with nuts.
 *
 * @todo refactor nuts.
 */
function _mapeditor_example_page_nuts() {

  // Fetches map default definition and settings.
  $map_defaults = _mapeditor_map_defaults();
  $map = $map_defaults['map'];
  $settings = $map_defaults['settings'];

  $map['center'] = array(48, 9);
  $map['zoom'] = 4;

  // Defines settings.
  $settings['height'] = 480;
  $settings['icon'] = 'green';

  $nuts = array(
    'NL' => array('title' => 'Netherlands', 'url' => 'http://example.com'),
    'BE' => array('title' => 'Belgium', 'url' => 'http://example.com'),
    'DE' => array('title' => 'Germany', 'url' => 'http://example.com'),
    'EL' => array('title' => 'Greece', 'url' => 'http://example.com'),
    'IE' => array('title' => 'Ireland', 'url' => 'http://example.com'),
    'SE' => array('title' => 'Sweden', 'url' => 'http://example.com'),
  );

  // Builds map.
  $mapeditor_map = new MapeditorMapBuild($map, $settings);
  $mapeditor_map->setCustomJs('nuts.js');
  $mapeditor_map->setNuts($nuts);
  return $mapeditor_map->build;
}

/**
 * Provides an example of a webtools map.
 *
 * Uses example.js so interference from Drupal is minimal. Is useful to have a
 * clean interaction with maps service.
 */
function _mapeditor_example_page_more() {
  global $base_url;
  $load_js = variable_get('webtools_environment', MAPEDITOR_WEBTOOLS_ENVIRONMENT);
  $element = array(
    '#type' => 'markup',
    '#markup' => "<script async src='${load_js}' type='text/javascript'></script>",
  );
  drupal_add_html_head($element, 'async_script');
  $js_path = $base_url . '/' . drupal_get_path('module', 'mapeditor') . '/js/example.js?v=' . rand(0, 33333);
  $options = drupal_json_encode(array(
      'service' => 'map',
      'custom' => $js_path,
    )
  );
  $build['script_init'] = array(
    '#type' => 'markup',
    '#markup' => "<script type='application/json'>${options}</script>",
  );
  $js_inline = "var map_height = '400px'";
  $build['#attached']['js'][] = array(
    'data' => $js_inline,
    'type' => 'inline',
    'scope' => 'header',
    'weight' => -10,
  );
  return $build;
}
