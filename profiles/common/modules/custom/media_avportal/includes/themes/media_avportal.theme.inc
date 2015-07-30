<?php
/**
 * @file
 * media_avportal/includes/themes/media_avportal.theme.inc
 *
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

  // Languages feature.
  $video_languages = $wrapper->getVideoLanguages();
  // Set current language.
  $query_params = drupal_get_query_parameters();
  $current_language = !empty($query_params['video-language']) ? $query_params['video-language'] : $GLOBALS['language']->language;
  if (in_array($current_language, $video_languages)) {
    $video_language = $current_language;
  }
  elseif (count($video_languages)) {
    $video_language = $video_languages[0];
  }
  else {
    $video_language = 'int';
  }
  $variables['video_language'] = str_replace('+', ' ', $video_language);

  // Build a language switcher if > 1 language available.
  if (count($video_languages) > 1) {
    $variables['language_switcher'] = theme('media_avportal_language_switcher', array(
        'languages' => $video_languages,
        'video_language' => $video_language,
    ));
  }

  // Add some options as their own template variables.
  foreach (array('width', 'height') as $theme_var) {
    $variables[$theme_var] = $variables['options'][$theme_var];
  }
}

/**
 * Theme function to display the language switcher.
 * 
 * note that the logic is done in javascript to circumvent the field cache
 * @see media_avportal.js
 */
function theme_media_avportal_language_switcher(&$vars) {
  $out = array();
  foreach ($vars['languages'] as $lng) {
    $current = $lng == $vars['video_language'] ? 'current' : '';
    $out[] = l($lng, current_path(), array('fragment' => $lng, 'attributes' => array('class' => array($current))));
  }
  return theme('item_list', array(
    'items' => $out,
    'title' => t('available languages')));
}
