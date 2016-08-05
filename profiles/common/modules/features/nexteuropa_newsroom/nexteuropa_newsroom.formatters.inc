<?php

/**
 * @file
 * Nexteuropa Newsroom formatter hooks.
 */

/**
 * Implements hook_field_formatter_info().
 */
function nexteuropa_newsroom_field_formatter_info() {
  return array(
    'newsroom_main_link' => array(
      'label' => t('Newsroom Main Link'),
      'field types' => array('link_field'),
      'multiple values' => FIELD_BEHAVIOR_DEFAULT,
    ),
    'newsroom_pathauto' => array(
      'label' => t('Newsroom Path Auto'),
      'field types' => array('text'),
      'multiple values' => FIELD_BEHAVIOR_DEFAULT,
    ),
    'newsroom_zoomable_image' => array(
      'label' => t('Newsroom image'),
      'field types' => array('image'),
      'settings' => _nexteuropa_newsroom_zoomable_formatter_settings(),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function nexteuropa_newsroom_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  switch ($display['type']) {

    case 'newsroom_zoomable_image':
      $image_styles = image_style_options(FALSE, PASS_THROUGH);
      $element['image_style'] = array(
        '#title' => t('Image style'),
        '#type' => 'select',
        '#default_value' => $settings['image_style'],
        '#empty_option' => t('None (original image)'),
        '#options' => $image_styles,
      );
      $element['zoomable'] = array(
        '#title' => t('Allow zoom (to original in fancybox)'),
        '#type' => 'checkbox',
        '#default_value' => $settings['zoomable'],
      );
      $element['display_title'] = array(
        '#title' => t('Display title'),
        '#type' => 'checkbox',
        '#default_value' => $settings['display_title'],
      );
      $element['display_copyright'] = array(
        '#title' => t('Display copyright'),
        '#type' => 'checkbox',
        '#default_value' => $settings['display_copyright'],
      );
      $element['display_caption'] = array(
        '#title' => t('Display caption'),
        '#type' => 'checkbox',
        '#default_value' => $settings['display_caption'],
      );
      break;

    case 'newsroom_main_link':
      $element['display_type'] = array(
        '#title' => t('Type of display context'),
        '#type' => 'select',
        '#options' => array(
          'default' => t('Default'),
          'title' => t('Title only'),
          'teaser' => t('Teaser also displayed'),
        ),
        '#default_value' => $settings['display_type'],
      );

      break;
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function nexteuropa_newsroom_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  if ($display['type'] == 'newsroom_main_link') {
    if ($display['settings']['display_type']) {
      $options = array(
        'default' => t('Default'),
        'title' => t('Title only'),
        'teaser' => t('Teaser also displayed'),
      );

      return $options[$display['settings']['display_type']];
    }
    else {
      return t('Default');
    }
  }

  if ($display['type'] == 'newsroom_zoomable_image') {
    $settings = $display['settings'];
    $summary = array();
    $image_styles = image_style_options(FALSE, PASS_THROUGH);
    unset($image_styles['']);
    if (isset($image_styles[$settings['image_style']])) {
      $summary[] = t('Image style: @style', array('@style' => $image_styles[$settings['image_style']]));
    }
    else {
      $summary[] = t('Original image');
    }
    if ($settings['zoomable']) {
      $summary[] = t('Is zoomable');
    }
    if ($settings['display_title']) {
      $summary[] = t('Displays title');
    }
    if ($settings['display_copyright']) {
      $summary[] = t('Displays copyright');
    }
    return implode(',', $summary);
  }
  return '';
}

/**
 * Implements hook_field_formatter_view().
 */
function nexteuropa_newsroom_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $elements = array();

  switch ($display['type']) {
    case 'newsroom_pathauto':
      foreach ($items as $delta => $item) {
        $elements[$delta] = array('#markup' => pathauto_cleanstring($item['safe_value']));
      }
      break;

    case 'newsroom_main_link':
      foreach ($items as $delta => $item) {
        if (!empty($item['url'])) {
          $item['url'] = NewsroomHelper::getNodeMainUrl($entity, $display['settings']['display_type']);
        }

        $elements[$delta] = array(
          '#theme' => 'link_formatter_link_absolute',
          '#element' => $item,
          '#field' => $instance,
          '#display' => $display,
        );
      }

      break;

    case 'newsroom_zoomable_image':
      global $language;
      foreach ($items as $delta => $item) {
        $image = array(
          'path' => $item['uri'],
        );
        $path_to_original = file_create_url($item['uri']);

        // Sets alt text.
        if (isset($item['field_file_image_alt_text'][$language->language][0])) {
          $image['alt'] = $item['field_file_image_alt_text'][$language->language][0]['safe_value'];
        }
        elseif (is_array($item) && array_key_exists('alt', $item)) {
          $image['alt'] = $item['alt'];
        }

        // Sets zoomability.
        $zoomable = $display['settings']['zoomable'] ? TRUE : FALSE;

        // Sets title.
        $title = NULL;
        if (isset($item['field_file_image_title_text'][$language->language][0])) {
          $image['title'] = $item['field_file_image_title_text'][$language->language][0]['safe_value'];
          if ($display['settings']['display_title']) {
            $title = $item['field_file_image_title_text'][$language->language][0]['safe_value'];
          }
        }
        elseif (isset($item['title']) && drupal_strlen($item['title']) > 0) {
          $image['title'] = $item['title'];
        }

        $copyright = NULL;

        // Sets copyright.
        if ($display['settings']['display_copyright']) {
          if (isset($item['field_newsroom_copyrights'][$language->language][0])) {
            $copyright = $item['field_newsroom_copyrights'][$language->language][0]['safe_value'];
          }
        }

        // Sets copyright.
        $caption = '';
        if ($display['settings']['display_caption']) {
          if (isset($item['field_caption'][$language->language][0])) {
            $caption = $item['field_caption'][$language->language][0]['safe_value'];
          }
        }

        if (isset($item['attributes'])) {
          $image['attributes'] = $item['attributes'];
        }

        if (isset($item['width']) && isset($item['height'])) {
          $image['width'] = $item['width'];
          $image['height'] = $item['height'];
        }

        $image['title'] = $title;

        if ($display['settings']['image_style']) {
          $image['style_name'] = $display['settings']['image_style'];
          $image_output = theme('image_style', $image);
        }
        else {
          $image_output = theme('image', $image);
        }

        $elements[$delta] = array(
          '#theme' => 'newsroom_zoomable_image',
          '#copyright' => $copyright,
          '#caption' => $caption,
          '#image_output' => $image_output,
          '#path_to_original' => $path_to_original,
          '#zoomable' => $zoomable,
        );
      }
      break;
  }

  return $elements;
}

/**
 * Returns zoomable formatter settings array.
 *
 * @param string $image_style
 *   Image style.
 * @param int $display_title
 *   Display title or not.
 * @param int $display_copyright
 *   Display copyright or not.
 * @param int $display_caption
 *   Display caption or not.
 * @param int $zoomable
 *   Is image zoomable or not.
 *
 * @return array
 *   Settings array.
 */
function _nexteuropa_newsroom_zoomable_formatter_settings($image_style = 'newsroom_style', $display_title = 1, $display_copyright = 1, $display_caption = 1, $zoomable = 1) {
  return array(
    'image_style' => $image_style,
    'display_title' => $display_title,
    'display_copyright' => $display_copyright,
    'display_caption' => $display_caption,
    'zoomable' => $zoomable,
  );
}
