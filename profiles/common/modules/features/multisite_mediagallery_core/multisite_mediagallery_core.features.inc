<?php

/**
 * @file
 * multisite_mediagallery_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function multisite_mediagallery_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function multisite_mediagallery_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function multisite_mediagallery_core_image_default_styles() {
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
          'width' => 600,
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'landscape',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function multisite_mediagallery_core_node_info() {
  $items = array(
    'gallerymedia' => array(
      'name' => t('Media Gallery'),
      'base' => 'node_content',
      'description' => t('A Gallery of Media.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
