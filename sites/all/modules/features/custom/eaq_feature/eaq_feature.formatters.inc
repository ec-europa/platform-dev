<?php

/**
 * @file
 * 
 */

/**
 * Implements hook_field_formatter_info().
 */
function eaq_feature_field_formatter_info() {
  return array(
    'text_user_name' => array(
      'label' => t('Display user name'), 
      'field types' => array('text'),
    ), 
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function eaq_feature_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  switch ($display['type']) {
    case 'text_user_name':
      foreach ($items as $delta => $item) {
        if (isset($item['value'])) {
          $user = user_load($item['value']);
          $name = $user->name;
        }
        $element[$delta] = array(
          '#markup' => (isset($name)) ? $name: '',
        );
      }
      break;
  }

  return $element;
}