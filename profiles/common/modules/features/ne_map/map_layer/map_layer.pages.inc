<?php

/**
 * Map layer view callback.
 */
function map_layer_view($map_layer) {
  drupal_set_title(entity_label('map_layer', $map_layer));
  return entity_view('map_layer', array(entity_id('map_layer', $map_layer) => $map_layer), 'default');
}
