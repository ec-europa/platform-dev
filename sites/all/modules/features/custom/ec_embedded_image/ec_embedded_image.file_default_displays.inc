<?php
/**
 * @file
 * ec_embedded_image.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function ec_embedded_image_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__default__media_flickr_video';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '560',
    'height' => '340',
    'autoplay' => 0,
  );
  $export['video__default__media_flickr_video'] = $file_display;

  return $export;
}
