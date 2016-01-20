<?php
/**
 * @file
 * Provides pages for the map entity.
 */

/**
 * Map view callback.
 */
function ne_map_view($map) {
  drupal_set_title(entity_label('ne_map', $map));
  return entity_view('ne_map', array(entity_id('ne_map', $map) => $map), 'full');
}

/**
 * Provides an example of a webtools map.
 *
 * Uses example.js so interference from Drupal is minimal. Is useful to have a
 * clean interaction with maps service.
 */
function ne_map_webtools() {
  global $base_url;
  $load_js = variable_get('webtools_environment', NE_MAP_WEBTOOLS_ENVIRONMENT);
  $element = array(
    '#type' => 'markup',
    '#markup' => "<script async src='${load_js}' type='text/javascript'></script>",
  );
  drupal_add_html_head($element, 'async_script');
  $js_path = $base_url . '/' . drupal_get_path('module', 'ne_map') . '/js/webtools.js?v=' . rand(0, 33333);
  $options = drupal_json_encode(array(
    'service' => 'map',
    'custom' => $js_path,
  ));
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
