<?php

/**
 * @file
 * cce_basic_config.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cce_basic_config_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_type") {
    return array("version" => "1");
  }
  if ($module == "password_policy" && $api == "default_password_policy") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cce_basic_config_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function cce_basic_config_image_default_styles() {
  $styles = array();

  // Exported image style: media_thumbnail_small.
  $styles['media_thumbnail_small'] = array(
    'name' => 'media_thumbnail_small',
    'label' => 'Media thumbnail small (50x50)',
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
          'width' => 50,
          'height' => 50,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: preview.
  $styles['preview'] = array(
    'label' => 'preview',
    'name' => 'preview',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 800,
          'height' => 600,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: square_thumbnail.
  $styles['square_thumbnail'] = array(
    'name' => 'square_thumbnail',
    'label' => 'Square thumbnail',
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
          'width' => 180,
          'height' => 180,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function cce_basic_config_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Use <em>articles</em> for time-sensitive content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_video_default_presets().
 */
function cce_basic_config_video_default_presets() {
  $items = array(
    'default_flash_conversion' => array(
      'name' => 'default_flash_conversion',
      'description' => 'Video H.264 MPEG-4 Audio AAC one-pass encoding',
      'settings' => array(
        'video_extension' => 'flv',
        'video_codec' => 'h264',
        'video_preset' => '',
        'video_quality' => 4,
        'video_speed' => 3,
        'wxh' => '640x360',
        'video_aspectmode' => 'preserve',
        'video_upscale' => 0,
        'audio_codec' => 'aac',
        'audio_quality' => 3,
        'deinterlace' => 'detect',
        'max_frame_rate' => '',
        'frame_rate' => '',
        'keyframe_interval' => '',
        'video_bitrate' => 566,
        'bitrate_cap' => '',
        'buffer_size' => '',
        'one_pass' => 1,
        'skip_video' => 0,
        'pixel_format' => '',
        'h264_profile' => '',
        'audio_bitrate' => '',
        'audio_channels' => 2,
        'audio_sample_rate' => 44100,
        'skip_audio' => 0,
        'video_watermark_enabled' => 0,
        'video_watermark_fid' => 0,
        'video_watermark_x' => 5,
        'video_watermark_y' => 5,
        'video_watermark_width' => '',
        'video_watermark_height' => '',
        'video_watermark_origin' => 'content',
        'autolevels' => 0,
        'deblock' => 0,
        'denoise' => '',
        'clip_start' => '',
        'clip_length' => '',
      ),
    ),
  );
  return $items;
}
