<?php

/**
 * @file
 * Theme and preprocess functions for Media: YouTube.
 */

/**
 * Preprocess function for theme('media_avportal_video').
 */
function media_avportal_preprocess_media_avportal_video(&$variables) {

  // Build the URI.
  $wrapper = file_stream_wrapper_get_instance_by_uri($variables['uri']);
  $parts = $wrapper->get_parameters();
  $variables['video_id'] = check_plain($parts['v']);

  // Add some options as their own template variables.
  foreach (array('width', 'height') as $theme_var) {
    $variables[$theme_var] = $variables['options'][$theme_var];
  }
}
