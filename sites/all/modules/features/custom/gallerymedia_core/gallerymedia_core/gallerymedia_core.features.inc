<?php
/**
 * @file
 * gallerymedia_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gallerymedia_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gallerymedia_core_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function gallerymedia_core_image_default_styles() {
  $styles = array();

  // Exported image style: landscape.
  $styles['landscape'] = array(
    'name' => 'landscape',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '600',
          'height' => '300',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function gallerymedia_core_node_info() {
  $items = array(
    'gallerymedia' => array(
      'name' => t('GalleryMedia'),
      'base' => 'node_content',
      'description' => t('A Gallery of Media.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_video_default_presets().
 */
function gallerymedia_core_video_default_presets() {
  $items = array(
    'default_flash_conversion' => array(
      'name' => 'default_flash_conversion',
      'description' => 'FLV transcoding for flash videos',
      'settings' => array(
        'video_extension' => 'flv',
        'video_codec' => 'flv',
        'video_preset' => '',
        'video_quality' => '3',
        'video_speed' => '3',
        'wxh' => '640x360',
        'video_aspectmode' => 'preserve',
        'video_upscale' => 0,
        'audio_codec' => 'libmp3lame',
        'audio_quality' => '3',
        'deinterlace' => 'detect',
        'max_frame_rate' => '',
        'frame_rate' => '',
        'keyframe_interval' => '',
        'video_bitrate' => '566',
        'bitrate_cap' => '',
        'buffer_size' => '',
        'one_pass' => 1,
        'skip_video' => 0,
        'pixel_format' => '',
        'h264_profile' => '',
        'audio_bitrate' => '',
        'audio_channels' => '2',
        'audio_sample_rate' => '44100',
        'skip_audio' => 0,
        'video_watermark_enabled' => 0,
        'video_watermark_fid' => 0,
        'video_watermark_x' => '5',
        'video_watermark_y' => '5',
        'video_watermark_width' => '',
        'video_watermark_height' => '',
        'video_watermark_origin' => 'content',
        'autolevels' => 0,
        'deblock' => 0,
        'denoise' => '',
        'clip_start' => '',
        'clip_length' => '',
      ),
      'overridden' => TRUE,
      'module' => 'gallerymedia_core',
    ),
    'default_video_conversion' => array(
      'name' => 'default_video_conversion',
      'description' => 'Default configuration for video conversion',
      'settings' => array(
        'video_extension' => 'mp4',
        'video_codec' => 'libx264',
        'video_preset' => 'libx264-slow',
        'video_quality' => '3',
        'video_speed' => '1',
        'wxh' => '640x480',
        'video_aspectmode' => 'preserve',
        'video_upscale' => 1,
        'audio_codec' => 'aac',
        'audio_quality' => '2',
        'deinterlace' => 'detect',
        'max_frame_rate' => '',
        'frame_rate' => '',
        'keyframe_interval' => '',
        'video_bitrate' => '',
        'bitrate_cap' => '',
        'buffer_size' => '',
        'one_pass' => 0,
        'skip_video' => 0,
        'audio_bitrate' => '',
        'audio_channels' => '2',
        'audio_sample_rate' => '',
        'skip_audio' => 0,
        'autolevels' => 1,
        'deblock' => 0,
        'denoise' => '0',
        'clip_start' => '',
        'clip_length' => '',
      ),
      'module' => 'gallerymedia_core',
      'overridden' => FALSE,
    ),
  );
  return $items;
}
