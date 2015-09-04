<?php

/**
 * @file
 * Provides build information for Mapeditor Map.
 */

/**
 * Class providing build definitions for a map.
 *
 * This class constructs the build drupal render array with the necessary
 * JavaScript and markup for the EC map service. It can provide geofield or
 * NUTS maps.
 */
class MapeditorMapBuild {

  // Holds filename of custom JavaScript to be passed to load.js.
  private $customJs;

  /**
   * Defines defaults for the map construction (both geofield and NUTS).
   */
  public function __construct($map, $settings) {
    $this->build = array();

    // Loads map service via load.js (general JavaScript service).
    $load_js = variable_get('webtools_environment', MAPEDITOR_WEBTOOLS_ENVIRONMENT);
    $element = array(
      '#type' => 'markup',
      '#markup' => "<script async src='$load_js' type='text/javascript'></script>",
    );
    drupal_add_html_head($element, 'async_script');

    // Prepares general map definitions and settings for JavaScript usage.
    $height = $settings['height'] . 'px';
    $mapeditor_map = drupal_json_encode($map);
    $settings = drupal_json_encode($settings);
    $js = "var map_height = '$height';\nvar mapeditor_map = $mapeditor_map;\nvar settings = $settings;";
    $this->build['#attached']['js'][] = array(
      'data' => $js,
      'type' => 'inline',
      'scope' => 'header',
      'weight' => -10,
    );
  }

  /**
   * Sets filename of custom JavaScript to be passed to load.js.
   */
  public function setCustomJs($custom_js) {
    $this->customJs = $custom_js;

    // Defines which custom JavaScript file to provide to load.js.
    $js_path = base_path() . drupal_get_path('module', 'mapeditor') . "/js/$this->customJs?v=" . rand(0, 33333);
    $options = drupal_json_encode(array(
        'service' => 'map',
        'custom' => $js_path,
      )
    );
    $this->build['load_js_vars'] = array(
      '#type' => 'markup',
      '#markup' => "<script type='application/json'>${options}</script>",
    );
  }

  /**
   * Defines map build array for geofield map data (coordinates).
   */
  public function setFeatures($features) {
    $features = drupal_json_encode($features);
    $features = "var features = $features\n";
    $this->build['#attached']['js'][] = array(
      'data' => $features,
      'type' => 'inline',
      'scope' => 'header',
      'weight' => -9,
    );
  }

  /**
   * Defines map build array for NUTS map data (NUTS region).
   */
  public function setNuts($nuts) {
    foreach ($nuts as $code => $nut) {
      $nuts_keys[] = $code;
    }
    $nuts = drupal_json_encode($nuts);
    $nuts_keys = drupal_json_encode($nuts_keys);
    $this->build['#attached']['js'][] = array(
      'data' => "var mapeditor_nuts = $nuts;\nvar mapeditor_nuts_keys = $nuts_keys;",
      'type' => 'inline',
      'scope' => 'header',
      'weight' => -9,
    );
  }

}
