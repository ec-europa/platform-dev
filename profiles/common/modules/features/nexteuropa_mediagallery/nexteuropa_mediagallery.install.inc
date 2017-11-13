<?php

/**
 * @file
 * Helper functions to install the feature Nexteuropa Galleries.
 */


/**
 * Enable gallery view modes for 'image' and 'video' bundles.
 */
function _nexteuropa_mediagallery_set_file_view_mode($mode = TRUE) {
  $variables = array("field_bundle_settings_file__image", "field_bundle_settings_file__video");
  $view_modes = array(
    'media_gallery_block',
    'media_gallery_node',
    'media_gallery_colorbox',
    'media_gallery_page',
  );

  foreach ($variables as $variable) {
    $var_value = variable_get($variable);
    foreach ($view_modes as $view_mode) {
      $var_value['view_modes'][$view_mode]['custom_settings'] = $mode;
    }
    variable_set($variable, $var_value);
  }
}
