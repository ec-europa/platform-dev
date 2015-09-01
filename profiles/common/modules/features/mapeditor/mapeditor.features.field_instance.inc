<?php
/**
 * @file
 * mapeditor.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mapeditor_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-mapeditor_map-body'
  $field_instances['node-mapeditor_map-body'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 66,
    ),
  );

  // Exported field_instance: 'node-mapeditor_map-mapeditor_csv_data'
  $field_instances['node-mapeditor_map-mapeditor_csv_data'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Enter comma separated values (CSV) in this format: latitude, longitude, name, description, link',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_csv_data',
    'label' => 'CSV data',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 12,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );
  // Exported field_instance: 'node-mapeditor_map-mapeditor_map_definition'
  $field_instances['node-mapeditor_map-mapeditor_map_definition'] = array(
    'bundle' => 'mapeditor_map',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Holds map definition. If you see this field contact your system administrator',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'popup' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'mapeditor_map_definition',
    'label' => 'Map definition',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 6,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('CSV data');
  t('Content to be shown on the map');
  t('Enter comma separated values (CSV) in this format: latitude, longitude, name, description, link');
  t('Height');
  t('Icon');
  t('Initial zoom');
  t('Map data');
  t('Maximum zoom level');
  t('Minimum zoom level');
  t('Popup');
  t('Select the kind of content that should be included in the map. If there are no options, then <a href="/admin/config/system/mapeditor/settings">configure content types</a> or contact the site administrator');
  t('The height in pixels of the map.');
  t('The maximum zoom level allowed. (How close in can you get?). If in doubt, 10 is a good level to start with');
  t('The minimum zoom level allowed. (How far away can you view from?). If in doubt, 2 is a good level to start with');
  t('The starting zoom level when this map is displayed. Restricted by min and max zoom settings. If in doubt, 4 is a good level to start with');
  t('Tile layer');
  t('Tile layer for the map');

  return $field_instances;
}
