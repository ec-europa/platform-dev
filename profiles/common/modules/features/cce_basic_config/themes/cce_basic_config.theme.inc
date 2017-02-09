<?php

/**
 * @file
 * Theme and preprocess functions for Media: YouTube.
 */

/**
 * Preprocess function for media video modules theme functions.
 *
 * It sets the no_wrapper variables for the different media video theme like
 * theme('media_youtube_video').
 *
 * @see cce_basic_config_theme_registry_alter()
 * @see _no_wrapper_youtube_file_formatter_video_view()
 */
function cce_basic_preprocess_common_file_video(&$variables) {
  if (isset($variables['options']['no_wrapper'])) {
    $variables['no_wrapper'] = $variables['options']['no_wrapper'];
  }
}
