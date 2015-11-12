<?php
/**
 * @file
 * multisite_metatags.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function multisite_metatags_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-contenttype-field_meta_classification'.
  $field_instances['node-contenttype-field_meta_classification'] = array(
    'bundle' => 'contenttype',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please select an IPG classification for your content. It will supply information to METADATA "Classification".<br/>This classification respects the <a href="http://ec.europa.eu/ipg/content/optimise/metadata/annex2_en.htm" target="_blank">IPG guidelines</a>.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_link',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_meta_classification',
    'label' => 'IPG Classification',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 41,
    ),
  );

  // Exported field_instance: 'node-contenttype-field_meta_description'.
  $field_instances['node-contenttype-field_meta_description'] = array(
    'bundle' => 'contenttype',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This text will supply information to METADATA "Description".<br/>It should respect the <a href="http://ec.europa.eu/ipg/content/optimise/metadata/annex1_en.htm#section_6" target="_blank">IPG guidelines</a>.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_meta_description',
    'label' => 'Description metatag',
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
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 3,
      ),
      'type' => 'text_textarea',
      'weight' => 42,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Description metatag');
  t('IPG Classification');
  t('Please select an IPG classification for your content. It will supply information to METADATA "Classification".<br/>This classification respects the <a href="http://ec.europa.eu/ipg/content/optimise/metadata/annex2_en.htm" target="_blank">IPG guidelines</a>.');
  t('This text will supply information to METADATA "Description".<br/>It should respect the <a href="http://ec.europa.eu/ipg/content/optimise/metadata/annex1_en.htm#section_6" target="_blank">IPG guidelines</a>.');

  return $field_instances;
}
