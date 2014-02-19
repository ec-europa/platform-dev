<?php
/**
 * @file
 * multisite_charts.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function multisite_charts_field_default_fields() {
  $fields = array();

  // Exported field: 'node-chart-field_chart_height'.
  $fields['node-chart-field_chart_height'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_chart_height',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'number',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'field_instance' => array(
      'bundle' => 'chart',
      'default_value' => array(
        0 => array(
          'value' => '400',
        ),
      ),
      'deleted' => '0',
      'description' => 'Height of the chart (in pixels). It should be an integer number between 100 and 800.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'diff_standard' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'print' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'rss' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'search_index' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
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
          'weight' => '2',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_chart_height',
      'label' => 'Height',
      'required' => 1,
      'settings' => array(
        'max' => '800',
        'min' => '100',
        'prefix' => '',
        'suffix' => 'px',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'number',
        'settings' => array(),
        'type' => 'number',
        'weight' => '30',
      ),
    ),
  );

  // Exported field: 'node-chart-field_chart_type'.
  $fields['node-chart-field_chart_type'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_chart_type',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '1',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'Column3D' => 'Single Series Charts - Column 3D',
          'Column2D' => 'Single Series Charts - Column 2D',
          'Line' => 'Single Series Charts - Line 2D',
          'Area2D' => 'Single Series Charts - Area 2D',
          'Bar2D' => 'Single Series Charts - Bar 2D',
          'Pie2D' => 'Single Series Charts - Pie 2D',
          'Pie3D' => 'Single Series Charts - Pie 3D',
          'Doughnut2D' => 'Single Series Charts - Doughnut 2D',
          'Doughnut3D' => 'Single Series Charts - Doughnut 3D',
          'Pareto2D' => 'Single Series Charts - Pareto 2D',
          'Pareto3D' => 'Single Series Charts - Pareto 3D',
          'MSColumn2D' => 'Multi-series Charts  - Multi-series Column 2D',
          'MSColumn3D' => 'Multi-series Charts  - Multi-series Column 3D',
          'MSLine' => 'Multi-series Charts  - Multi-series Line 2D',
          'MSBar2D' => 'Multi-series Charts  - Multi-series Bar 2D',
          'MSBar3D' => 'Multi-series Charts  - Multi-series Bar 3D',
          'MSArea' => 'Multi-series Charts  - Multi-series Area 2D',
          'Marimekko' => 'Multi-series Charts  - Marimekko',
          'ZoomLine' => 'Multi-series Charts  - Zoom Line',
          'StackedColumn3D' => 'Stacked Charts - Stacked Column 3D',
          'StackedColumn2D' => 'Stacked Charts - Stacked Column 2D',
          'StackedBar2D' => 'Stacked Charts - Stacked Bar 2D',
          'StackedBar3D' => 'Stacked Charts - Stacked Bar 3D',
          'StackedArea2D' => 'Stacked Charts - Stacked Area 2D',
          'MSStackedColumn2D' => 'Stacked Charts - Multi-series Stacked Column 2D',
          'MSCombi3D' => 'Combination Charts - True 3D Chart (Multi-series 3D Single Y Combination chart - Column + Line + Area)',
          'MSCombi2D' => 'Combination Charts - Multi-series 2D Single Y Combination Chart (Column + Line + Area)',
          'MSColumnLine3D' => 'Combination Charts - Multi-series Column 3D + Multi-series Line - Single Y Axis',
          'StackedColumn2DLine' => 'Combination Charts - Stacked Column2D + Line single Y Axis',
          'StackedColumn3DLine' => 'Combination Charts - Stacked Column3D + Line single Y Axis',
          'MSCombiDY2D' => 'Combination Charts - Multi-series 2D Dual Y Combination Chart (Column + Line + Area)',
          'MSColumn3DLineDY' => 'Combination Charts - Multi-series Column 3D + Multi-series Line - Dual Y Axis',
          'StackedColumn3DLineDY' => 'Combination Charts - Stacked Column 3D + Line Dual Y Axis',
          'MSStackedColumn2DLineDY' => 'Combination Charts - Multi-series Stacked Column 2D + Line Dual Y Axis',
          'Scatter' => 'XY Plot Charts - Scatter Chart',
          'Bubble' => 'XY Plot Charts - Bubble Chart',
          'ScrollColumn2D' => 'Scroll Charts - Scroll Column 2D',
          'ScrollLine2D' => 'Scroll Charts - Scroll Line 2D',
          'ScrollArea2D' => 'Scroll Charts - Scroll Area 2D',
          'ScrollStackedColumn2D' => 'Scroll Charts - Scroll Stacked Column 2D',
          'ScrollCombi2D' => 'Scroll Charts - Scroll Combination 2D (Single Y)',
          'ScrollCombiDY2D' => 'Scroll Charts - Scroll Combination 2D (Dual Y)',
          'SSGrid' => 'Others - Single Series Grid Component',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'chart',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'Select a chart type from the list.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'diff_standard' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'print' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'rss' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'search_index' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
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
          'weight' => '0',
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
        'weight' => '40',
      ),
    ),
  );

  // Exported field: 'node-chart-field_chart_width'.
  $fields['node-chart-field_chart_width'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_chart_width',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'number',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'field_instance' => array(
      'bundle' => 'chart',
      'default_value' => array(
        0 => array(
          'value' => '400',
        ),
      ),
      'deleted' => '0',
      'description' => 'Width of the chart (in pixels). It should be an integer number between 100 and 800.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'diff_standard' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'print' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'rss' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'search_index' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
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
          'weight' => '1',
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_chart_width',
      'label' => 'Width',
      'required' => 1,
      'settings' => array(
        'max' => '800',
        'min' => '100',
        'prefix' => '',
        'suffix' => 'px',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'number',
        'settings' => array(),
        'type' => 'number',
        'weight' => '20',
      ),
    ),
  );

  // Exported field: 'node-chart-field_chart_xml_data_source'.
  $fields['node-chart-field_chart_xml_data_source'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_chart_xml_data_source',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'xml_field',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'xml_field_xml',
    ),
    'field_instance' => array(
      'bundle' => 'chart',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'FusionCharts takes in data only in custom XML format. The XML can be auto-generated using the <a href="http://www.cc.cec/fpfis/fusioncharts/Tools/XMLGenerator/XMLGen/XMLGen_1.html" target="_blank">FusionCharts XML Generator Utility</a> which provides a spreadsheet layout for convenient data entry.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
        'diff_standard' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
        'print' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
        'rss' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
        'search_index' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
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
          'weight' => '3',
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
        'weight' => '10',
      ),
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

  return $fields;
}
