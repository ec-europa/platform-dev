<?php

/**
 * @file
 * multisite_maps.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function multisite_maps_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-map-field_map_height'.
  $field_instances['node-map-field_map_height'] = array(
    'bundle' => 'map',
    'default_value' => array(
      0 => array(
        'value' => 400,
      ),
    ),
    'deleted' => 0,
    'description' => 'Height of the map (in pixels). It should be an integer number between 100 and 800.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
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
    'field_name' => 'field_map_height',
    'label' => 'Height',
    'required' => 1,
    'settings' => array(
      'max' => 800,
      'min' => 100,
      'prefix' => '',
      'suffix' => 'px',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 40,
    ),
  );

  // Exported field_instance: 'node-map-field_map_type'.
  $field_instances['node-map-field_map_type'] = array(
    'bundle' => 'map',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Select a map type from the list.',
    'display' => array(
      'default' => array(
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
    'field_name' => 'field_map_type',
    'label' => 'Map type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'node-map-field_map_width'.
  $field_instances['node-map-field_map_width'] = array(
    'bundle' => 'map',
    'default_value' => array(
      0 => array(
        'value' => 400,
      ),
    ),
    'deleted' => 0,
    'description' => 'Width of the map (in pixels). It should be an integer number between 100 and 800.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
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
    'field_name' => 'field_map_width',
    'label' => 'Width',
    'required' => 1,
    'settings' => array(
      'max' => 800,
      'min' => 100,
      'prefix' => '',
      'suffix' => 'px',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 30,
    ),
  );

  // Exported field_instance: 'node-map-field_map_xml_data_source'.
  $field_instances['node-map-field_map_xml_data_source'] = array(
    'bundle' => 'map',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'FusionMaps takes in data only in custom XML format. The XML can be auto-generated using the <a href="https://webtools.ec.europa.eu/fusionmapsxt/Tools/GUI/FusionMapsGUI.html" target="_blank">Visual Map Builder</a> which provides an online interface for convenient data entry.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_map_xml_data_source',
    'label' => 'Data XML Source',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'xml_field',
      'settings' => array(),
      'type' => 'xml_field_text',
      'weight' => 10,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Data XML Source');
  t('FusionMaps takes in data only in custom XML format. The XML can be auto-generated using the <a href="https://webtools.ec.europa.eu/fusionmapsxt/Tools/GUI/FusionMapsGUI.html" target="_blank">Visual Map Builder</a> which provides an online interface for convenient data entry.');
  t('Height');
  t('Height of the map (in pixels). It should be an integer number between 100 and 800.');
  t('Map type');
  t('Select a map type from the list.');
  t('Width');
  t('Width of the map (in pixels). It should be an integer number between 100 and 800.');

  return $field_instances;
}
