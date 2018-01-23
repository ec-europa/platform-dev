<?php

/**
 * @file
 * multisite_charts.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function multisite_charts_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_chart_height'.
  $field_bases['field_chart_height'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_chart_height',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'number',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_chart_type'.
  $field_bases['field_chart_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_chart_type',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 1,
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
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_chart_width'.
  $field_bases['field_chart_width'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_chart_width',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'number',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_chart_xml_data_source'.
  $field_bases['field_chart_xml_data_source'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_chart_xml_data_source',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'xml_field',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'xml_field_xml',
  );

  return $field_bases;
}
