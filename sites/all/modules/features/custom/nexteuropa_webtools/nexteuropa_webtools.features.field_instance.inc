<?php
/**
 * @file
 * nexteuropa_webtools.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function nexteuropa_webtools_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'bean-webtools-field_json_object'
  $field_instances['bean-webtools-field_json_object'] = array(
    'bundle' => 'webtools',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'nexteuropa_json_field',
        'settings' => array(),
        'type' => 'json_settings_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'bean',
    'field_name' => 'field_json_object',
    'label' => 'JSON Object',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'basic_html' => 'basic_html',
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'basic_html' => array(
              'weight' => 5,
            ),
            'filtered_html' => array(
              'weight' => -9,
            ),
            'full_html' => array(
              'weight' => -10,
            ),
            'plain_text' => array(
              'weight' => -8,
            ),
          ),
        ),
      ),
      'js_to_load' => array(
        'nexteuropa_webtools_smartloader_prurl' => 'nexteuropa_webtools_smartloader_prurl',
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('JSON Object');

  return $field_instances;
}
