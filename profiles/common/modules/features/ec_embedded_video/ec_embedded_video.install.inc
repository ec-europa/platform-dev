<?php
/**
 * @file
 * Code for the ec_embedded_video module.
 */

/**
 * Soft configure media assets video display for the WYSIWYG view mode.
 *
 * Implied media assets are YouTube, Vimeo, Dailymotion and AV portal.
 */
function _ec_embedded_video_install_soft_configured_file_display() {

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__no_wrapper_media_avportal_video';
  $file_display->weight = -39;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '390',
  );
  file_display_save($file_display);

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__no_wrapper_media_dailymotion_video';
  $file_display->weight = -43;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '560',
    'height' => '340',
    'autoplay' => 0,
    'iframe' => 1,
  );
  file_display_save($file_display);

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__no_wrapper_media_vimeo_video';
  $file_display->weight = -49;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '360',
    'color' => '',
    'protocol_specify' => 0,
    'protocol' => 'https://',
    'autoplay' => 0,
    'loop' => 0,
    'title' => 1,
    'byline' => 1,
    'portrait' => 1,
    'api' => 0,
  );
  file_display_save($file_display);

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__no_wrapper_media_youtube_video';
  $file_display->weight = -46;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '390',
    'theme' => 'dark',
    'color' => 'red',
    'autohide' => '2',
    'autoplay' => 0,
    'loop' => 0,
    'showinfo' => 1,
    'modestbranding' => 0,
    'rel' => 1,
    'nocookie' => 0,
    'protocol_specify' => 0,
    'protocol' => 'https:',
    'enablejsapi' => 0,
    'origin' => '',
  );
  file_display_save($file_display);

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__media_avportal_video';
  $file_display->weight = -41;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '390',
  );
  file_display_save($file_display);

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__media_dailymotion_video';
  $file_display->weight = -40;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '560',
    'height' => '340',
    'autoplay' => 0,
    'iframe' => 1,
  );
  file_display_save($file_display);

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__media_vimeo_video';
  $file_display->weight = -47;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '360',
    'color' => '',
    'protocol_specify' => 0,
    'protocol' => 'https://',
    'autoplay' => 0,
    'loop' => 0,
    'title' => 1,
    'byline' => 1,
    'portrait' => 1,
    'api' => 0,
  );
  file_display_save($file_display);

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__wysiwyg__media_youtube_video';
  $file_display->weight = -46;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '390',
    'theme' => 'dark',
    'color' => 'red',
    'autohide' => '2',
    'autoplay' => 0,
    'loop' => 0,
    'showinfo' => 1,
    'modestbranding' => 0,
    'rel' => 1,
    'nocookie' => 0,
    'protocol_specify' => 0,
    'protocol' => 'https:',
    'enablejsapi' => 0,
    'origin' => '',
  );
  file_display_save($file_display);
}
