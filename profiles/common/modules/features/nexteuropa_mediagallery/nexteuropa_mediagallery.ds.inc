<?php

/**
 * @file
 * nexteuropa_mediagallery.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function nexteuropa_mediagallery_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'media_gallery_block';
  $ds_view_mode->label = 'Media Gallery Landscape';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['media_gallery_block'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'media_gallery_colorbox';
  $ds_view_mode->label = 'Media Gallery Colorbox';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['media_gallery_colorbox'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'media_gallery_node';
  $ds_view_mode->label = 'Media Gallery';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['media_gallery_node'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'media_gallery_page';
  $ds_view_mode->label = 'Media Gallery thumbnail';
  $ds_view_mode->entities = array(
    'node' => 'node',
    'file' => 'file',
  );
  $export['media_gallery_page'] = $ds_view_mode;

  return $export;
}
