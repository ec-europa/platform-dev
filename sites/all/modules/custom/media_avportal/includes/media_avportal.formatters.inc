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

  foreach (array('width', 'height', 'autohide', 'autoplay', 'color',
    'enablejsapi', 'loop', 'modestbranding', 'nocookie', 'origin', 'protocol',
    'protocol_specify', 'rel', 'showinfo', 'theme') as $setting) {
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
    $element = array(
      '#theme' => 'media_avportal_video',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height', 'autohide', 'autoplay', 'color',
      'enablejsapi', 'loop', 'modestbranding', 'nocookie', 'origin', 'protocol',
      'protocol_specify', 'rel', 'showinfo', 'theme', 'attributes') as $setting) {
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

  // @see https://developers.google.com/avportal/player_parameters#Parameters
  // Multiple options.
  $element['theme'] = array(
    '#title' => t('Player theme'),
    '#type' => 'radios',
    '#options' => array(
      'dark' => t('Dark'),
      'light' => t('Light'),
    ),
    '#default_value' => $settings['theme'],
  );
  $element['color'] = array(
    '#title' => t('Progress bar color'),
    '#type' => 'radios',
    '#options' => array(
      'red' => t('Red'),
      'white' => t('White'),
    ),
    '#default_value' => $settings['color'],
  );
  $element['autohide'] = array(
    '#title' => t('Controls during playback'),
    '#type' => 'radios',
    '#options' => array(
      '0' => t('Keep progress bar and player controls on screen while playing'),
      '2' => t('Hide progress bar while playing'),
      '1' => t('Hide progress bar and player controls'),
    ),
    '#default_value' => $settings['autohide'],
  );

  // Single Options.
  $element['autoplay'] = array(
    '#title' => t('Autoplay video on load'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
  );
  $element['loop'] = array(
    '#title' => t('Loop video'),
    '#type' => 'checkbox',
    '#default_value' => $settings['loop'],
  );

  // Note: make sure the positive/negitive language lines up with option
  // processing in media_avportal.theme.inc.
  $element['showinfo'] = array(
    '#title' => t('Display video title and uploader'),
    '#type' => 'checkbox',
    '#default_value' => $settings['showinfo'],
  );
  $element['modestbranding'] = array(
    '#title' => t('Remove AV Portal logo from the control bar'),
    '#type' => 'checkbox',
    '#default_value' => $settings['modestbranding'],
  );
  $element['rel'] = array(
    '#title' => t('Show related videos when playback ends'),
    '#type' => 'checkbox',
    '#default_value' => $settings['rel'],
  );
  $element['nocookie'] = array(
    '#title' => t('Use privacy enhanced (no cookie) mode'),
    '#type' => 'checkbox',
    '#default_value' => $settings['nocookie'],
  );
  $element['protocol_specify'] = array(
    '#title' => t('Specify an http protocol'),
    '#type' => 'checkbox',
    '#default_value' => $settings['protocol_specify'],
    '#description' => t('An explicit protocol may be neccesary for videos embedded in RSS feeds and emails. If no protocol is specified, iframes will be protocol relative.'),
  );
  $element['protocol'] = array(
    '#title' => t('Iframe protocol'),
    '#type' => 'radios',
    '#default_value' => $settings['protocol'],
    '#options' => array(
      'http:' => 'http://',
      'https:' => 'https://',
    ),
    '#states' => array(
      'invisible' => array(
        ':input[name="displays[media_avportal_video][settings][protocol_specify]"]' => array('checked' => FALSE),
      ),
    ),
  );

  // JS api.
  $element['enablejsapi'] = array(
    '#title' => t('Enable the <a href="https://developers.google.com/avportal/js_api_reference">Javascript API</a>'),
    '#type' => 'checkbox',
    '#default_value' => $settings['enablejsapi'],
    '#description' => 'An id in the format <code>media-avportal-{video_id}</code> will be added to each iframe.',
  );
  $element['origin'] = array(
    '#title' => t('Origin'),
    '#type' => 'textfield',
    '#description' => t("If the Javascript API is enabled, enter your site's domain for added security."),
    '#default_value' => $settings['origin'],
    '#states' => array(
      'invisible' => array(
        ':input[name="displays[media_avportal_video][settings][enablejsapi]"]' => array('checked' => FALSE),
      ),
    ),
    '#element_validate' => array('_avportal_validate_jsapi_domain'),
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
 * Validation for Js API Origin.
 */
function _avportal_validate_jsapi_domain($element, &$form_state, $form) {

  // Check if the value is a url with http/s and no trailing directories.
  if (!empty($element['#value']) && !preg_match('/^https?\:\/\/[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,4}){1,2}$/', $element['#value'])) {
    form_error($element, t('Please insert a valid domain in the format http://www.yourdomain.com'));
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_avportal_file_formatter_image_view($file, $display, $langcode) {
  if (isset($file->filemime) && $file->filemime == 'video/avportal') {
    $path = base_path() . drupal_get_path('module', 'media_avportal') . '/img/avportal.png';
    $element = array(
      '#theme' => 'image',
      '#path' => $path,
      '#alt' => $file->filename,
    );
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
      'autoplay' => media_avportal_variable_get('autoplay'),
    ),
    'teaser' => array(
      'width' => 560,
      'height' => 340,
      'autoplay' => media_avportal_variable_get('autoplay'),
    ),
    'preview' => array(
      'width' => 640,
      'height' => 390,
      'autoplay' => media_avportal_variable_get('autoplay'),
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
    'default' => 'large',
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
