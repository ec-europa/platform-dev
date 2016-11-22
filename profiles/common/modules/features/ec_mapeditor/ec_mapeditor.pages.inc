<?php
/**
 * @file
 * Provides pages for the map entity.
 */

/**
 * Map view callback.
 */
function _ec_mapeditor_view($map) {
  drupal_set_title(entity_label('map', $map));
  return entity_view('map', array(entity_id('map', $map) => $map), 'full');
}

/**
 * Provides a page with a webtools map.
 *
 * @return array
 *   Build array for map page.
 */
function _ec_mapeditor_webtools() {
  global $base_url;
  $load_js = variable_get('ec_mapeditor_webtools_environment', EC_MAPEDITOR_WEBTOOLS_ENVIRONMENT);
  $element = array(
    '#type' => 'markup',
    '#markup' => "<script async src='${load_js}' type='text/javascript'></script>",
  );
  drupal_add_html_head($element, 'async_script');
  $js_path = $base_url . '/' . drupal_get_path('module', 'ec_mapeditor') . '/js/webtools.js?v=' . rand(0, 33333);
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
