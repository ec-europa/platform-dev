<?php

/**
 * Map view callback.
 */
function ne_map_view($map) {
  drupal_set_title(entity_label('ne_map', $map));
  return entity_view('ne_map', array(entity_id('ne_map', $map) => $map), 'full');
}
