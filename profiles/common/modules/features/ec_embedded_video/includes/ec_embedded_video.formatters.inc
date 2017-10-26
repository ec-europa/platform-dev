<?php

/**
 * @file
 * File formatters for Platform needs.
 */

/**
 * Implements hook_file_formatter_info_alter().
 *
 * It alters file_formatter_info to add the "Wrapper free formatters for the
 * different Video-sharing services (YouTube, Vimeo, Dailymotion and
 * AV portal).
 */
function ec_embedded_video_file_formatter_info_alter(&$info) {
  if (module_exists('media_youtube')) {
    $formatter = $info['media_youtube_video'];
    $formatter['label'] = t('YouTube Video Without Wrapper');
    $formatter['description'] = t(
      'It works like the "YouTube Video" formatter but it does not wrap the 
      video tags by HTML containers like "div"'
    );
    $formatter['view callback'] = '_no_wrapper_youtube_file_formatter_video_view';
    $info['no_wrapper_media_youtube_video'] = $formatter;
  }

  if (module_exists('media_vimeo')) {
    $formatter = $info['media_vimeo_video'];
    $formatter['label'] = t('Vimeo Video Without Wrapper');
    $formatter['description'] = t(
      'It works like the "Vimeo Video" Wrapper but it does not wrap the 
      video tags by HTML containers like "div"'
    );
    $formatter['view callback'] = '_no_wrapper_vimeo_file_formatter_video_view';
    $info['no_wrapper_media_vimeo_video'] = $formatter;
  }

  if (module_exists('media_dailymotion')) {
    $formatter = $info['media_dailymotion_video'];
    $formatter['label'] = t('Dailymotion Video Without Wrapper');
    $formatter['description'] = t(
      'It works like the "Dailymotion Video" Wrapper but it does not wrap the 
      video tags by HTML containers like "div"'
    );
    $formatter['view callback'] = '_no_wrapper_dailymotion_file_formatter_video_view';
    $info['no_wrapper_media_dailymotion_video'] = $formatter;
  }

  if (module_exists('media_avportal')) {
    $formatter = $info['media_avportal_video'];
    $formatter['label'] = t('AV Portal Video Without Wrapper');
    $formatter['description'] = t(
      'It works like the "AV Portal Video" Wrapper but it does not wrap the 
      video tags by HTML containers like "div"'
    );
    $formatter['view callback'] = '_no_wrapper_avportal_file_formatter_video_view';
    $info['no_wrapper_media_avportal_video'] = $formatter;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 *
 * It adds the 'no_wrapper' variable value in options of the YouTube video
 * elements.
 */
function _no_wrapper_youtube_file_formatter_video_view($file, $display, $langcode) {
  $element = media_youtube_file_formatter_video_view($file, $display, $langcode);

  if (!empty($element)) {
    $element['#options']['no_wrapper'] = TRUE;
  }

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 *
 * It adds the 'no_wrapper' variable value in options of the Vimeo video
 * elements.
 */
function _no_wrapper_vimeo_file_formatter_video_view($file, $display, $langcode) {
  $element = media_vimeo_file_formatter_video_view($file, $display, $langcode);

  if (!empty($element)) {
    $element['#options']['no_wrapper'] = TRUE;
  }

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 *
 * It adds the 'no_wrapper' variable value in options of the Dailymotion video
 * elements.
 */
function _no_wrapper_dailymotion_file_formatter_video_view($file, $display, $langcode) {
  $element = media_dailymotion_file_formatter_video_view($file, $display, $langcode);

  if (!empty($element)) {
    $element['#options']['no_wrapper'] = TRUE;
  }

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 *
 * It adds the 'no_wrapper' variable value in options of the AV portal video
 * elements.
 */
function _no_wrapper_avportal_file_formatter_video_view($file, $display, $langcode) {
  $element = media_avportal_file_formatter_video_view($file, $display, $langcode);

  if (!empty($element)) {
    $element['#options']['no_wrapper'] = TRUE;
  }

  return $element;
}
