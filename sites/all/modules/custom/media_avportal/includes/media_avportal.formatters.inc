<?php
/**
 * @file
 * media_avportal/includes/media_avportal.formatters.inc
 *
 * Formatters for Media: Avportal.
 */

/**
 * Implements hook_file_formatter_info().
 */
function media_avportal_file_formatter_info() {
  $formatters['media_avportal_video'] = array(
    'label' => t('AV Portal Video'),
    'file types' => array('video'),
    'default settings' => array(),
    'view callback' => 'media_avportal_file_formatter_video_view',
    'settings callback' => 'media_avportal_file_formatter_video_settings',
  );

  foreach (array('width', 'height') as $setting) {
    $formatters['media_avportal_video']['default settings'][$setting] = media_avportal_variable_get($setting);
  }

  $formatters['media_avportal_image'] = array(
    'label' => t('AV Portal Preview Image'),
    'file types' => array('video'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'media_avportal_file_formatter_image_view',
    'settings callback' => 'media_avportal_file_formatter_image_settings',
  );

  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_avportal_file_formatter_video_view($file, $display, $langcode) {

  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'avportal' && empty($file->override['wysiwyg'])) {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $languages = $wrapper->getVideoLanguages();
    $element = array(
      '#theme' => 'media_avportal_video',
      '#uri' => $file->uri,
      '#options' => array('languages' => $languages),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height') as $setting) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_avportal_file_formatter_video_settings($form, &$form_state, $settings) {
  $element = array();

  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
    '#element_validate' => array('_avportal_validate_video_width_and_height'),
  );
  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
    '#element_validate' => array('_avportal_validate_video_width_and_height'),
  );

  return $element;
}

/**
 * Validation for width and height.
 */
function _avportal_validate_video_width_and_height($element, &$form_state, $form) {

  // Check if the value is a number with an optional decimal or
  // percentage sign, or "auto".
  if (!empty($element['#value']) && !preg_match('/^(auto|([0-9]*(\.[0-9]+)?%?))$/', $element['#value'])) {
    form_error($element, t("The value entered for @dimension is invalid. Please insert a unitless integer for pixels, a percent, or 'auto'. Note that percent and auto may not function correctly depending on the browser and doctype.", array('@dimension' => $element['#title'])));
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_avportal_file_formatter_image_view($file, $display, $langcode) {
  if (isset($file->filemime) && $file->filemime == 'video/avportal') {

    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);
    $video_thumb = $wrapper->getVideoThumb();
    $element = array(
      '#theme' => 'image_style',
      '#style_name' => $image_style,
      '#path' => $wrapper->getLocalThumbnailPath($video_thumb),
      '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename);
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_avportal_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  return $element;
}

/**
 * Implements hook_file_default_displays().
 */
function media_avportal_file_default_displays() {

  // Default settings for displaying as a video.
  $default_displays = array();

  $default_video_settings = array(
    'default' => array(
      'width' => 640,
      'height' => 390,
    ),
    'teaser' => array(
      'width' => 560,
      'height' => 340,
    ),
    'preview' => array(
      'width' => 640,
      'height' => 390,
    ),
  );
  foreach ($default_video_settings as $view_mode => $settings) {
    $display_name = 'video__' . $view_mode . '__media_avportal_video';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 1,
      'settings' => $settings,
    );
  }

  // Default settings for displaying a video preview image.
  // We enable preview images even for view modes that also play video
  // for use inside a running WYSIWYG editor. We weight them so video
  // formatters come first in the cascade to make sure the video formatter
  // is used whenever possible.
  $default_image_styles = array(
    'default' => 'medium',
    'preview' => 'media_thumbnail',
    'teaser' => '',
    // Legacy view modes, see note above.
  );
  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'video__' . $view_mode . '__media_avportal_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 2,
      'settings' => array('image_style' => $image_style),
    );
  }

  return $default_displays;
}
