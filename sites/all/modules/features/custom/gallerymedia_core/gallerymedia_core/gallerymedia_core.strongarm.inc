<?php
/**
 * @file
 * gallerymedia_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function gallerymedia_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_gallerymedia';
  $strongarm->value = '0';
  $export['comment_anonymous_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_gallerymedia';
  $strongarm->value = 0;
  $export['comment_default_mode_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_gallerymedia';
  $strongarm->value = '10';
  $export['comment_default_per_page_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_gallerymedia';
  $strongarm->value = 0;
  $export['comment_form_location_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_gallerymedia';
  $strongarm->value = '0';
  $export['comment_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_gallerymedia';
  $strongarm->value = '0';
  $export['comment_preview_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_gallerymedia';
  $strongarm->value = 0;
  $export['comment_subject_field_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_gallerymedia';
  $strongarm->value = '2';
  $export['language_content_type_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_gallerymedia';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_gallerymedia';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_gallerymedia';
  $strongarm->value = array(
    0 => 'moderation',
    1 => 'revision',
  );
  $export['node_options_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_gallerymedia';
  $strongarm->value = '0';
  $export['node_preview_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_gallerymedia';
  $strongarm->value = 0;
  $export['node_submitted_gallerymedia'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sweaver_paths';
  $strongarm->value = 'admin*
node/add*
node/*/edit
node/*/panel*
panels/ajax*
user/*/edit
batch*
media/browser*';
  $export['sweaver_paths'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_autobuffering';
  $strongarm->value = 0;
  $export['video_autobuffering'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_autoplay';
  $strongarm->value = 0;
  $export['video_autoplay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_bypass_conversion';
  $strongarm->value = 0;
  $export['video_bypass_conversion'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_convertor';
  $strongarm->value = 'TranscoderAbstractionFactoryFfmpeg';
  $export['video_convertor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_convert_on_save';
  $strongarm->value = 0;
  $export['video_convert_on_save'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_ffmpeg_path';
  $strongarm->value = '/usr/bin/ffmpeg';
  $export['video_ffmpeg_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_preset';
  $strongarm->value = array(
    'default_video_conversion' => 'default_video_conversion',
  );
  $export['video_preset'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_publish_on_complete';
  $strongarm->value = FALSE;
  $export['video_publish_on_complete'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_thumbnail_count';
  $strongarm->value = '3';
  $export['video_thumbnail_count'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_thumbnail_path';
  $strongarm->value = 'videos/thumbnails';
  $export['video_thumbnail_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_use_default_thumb';
  $strongarm->value = 0;
  $export['video_use_default_thumb'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'video_use_preset_wxh';
  $strongarm->value = 1;
  $export['video_use_preset_wxh'] = $strongarm;

  return $export;
}
