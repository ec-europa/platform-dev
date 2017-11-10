<?php

/**
 * @file
 * multisite_charts.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function multisite_charts_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-chart-field_chart_height'.
  $field_instances['node-chart-field_chart_height'] = array(
    'bundle' => 'chart',
    'default_value' => array(
      0 => array(
        'value' => 400,
      ),
    ),
    'deleted' => 0,
    'description' => 'Height of the chart (in pixels). It should be an integer number between 100 and 800.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'diff_standard' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'print' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'rss' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'search_result' => array(
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
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_chart_height',
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
      'weight' => 30,
    ),
  );

  // Exported field_instance: 'node-chart-field_chart_type'.
  $field_instances['node-chart-field_chart_type'] = array(
    'bundle' => 'chart',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Select a chart type from the list.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'diff_standard' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'print' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'rss' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'search_result' => array(
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
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_chart_type',
    'label' => 'Chart type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 40,
    ),
  );

  // Exported field_instance: 'node-chart-field_chart_width'.
  $field_instances['node-chart-field_chart_width'] = array(
    'bundle' => 'chart',
    'default_value' => array(
      0 => array(
        'value' => 400,
      ),
    ),
    'deleted' => 0,
    'description' => 'Width of the chart (in pixels). It should be an integer number between 100 and 800.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'diff_standard' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'print' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'rss' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'search_result' => array(
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
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_chart_width',
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
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'node-chart-field_chart_xml_data_source'.
  $field_instances['node-chart-field_chart_xml_data_source'] = array(
    'bundle' => 'chart',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'FusionCharts takes in data only in custom XML format. The XML can be auto-generated using the <a href="http://www.cc.cec/fpfis/fusioncharts/Tools/XMLGenerator/XMLGen/XMLGen_1.html" target="_blank">FusionCharts XML Generator Utility</a> which provides a spreadsheet layout for convenient data entry.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'diff_standard' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'print' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'rss' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'search_result' => array(
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
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_chart_xml_data_source',
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
  t('Chart type');
  t('Data XML Source');
  t('FusionCharts takes in data only in custom XML format. The XML can be auto-generated using the <a href="http://www.cc.cec/fpfis/fusioncharts/Tools/XMLGenerator/XMLGen/XMLGen_1.html" target="_blank">FusionCharts XML Generator Utility</a> which provides a spreadsheet layout for convenient data entry.');
  t('Height');
  t('Height of the chart (in pixels). It should be an integer number between 100 and 800.');
  t('Select a chart type from the list.');
  t('Width');
  t('Width of the chart (in pixels). It should be an integer number between 100 and 800.');

  return $field_instances;
}
