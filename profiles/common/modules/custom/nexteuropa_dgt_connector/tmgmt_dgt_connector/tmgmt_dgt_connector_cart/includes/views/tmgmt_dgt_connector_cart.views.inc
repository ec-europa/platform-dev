<?php

/**
 * @file
 * Extra view functionality for translation carts.
 */

/**
 * Implements hook_views_data_alter().
 */
function tmgmt_dgt_connector_cart_views_data_alter(&$data) {
  $data['cart_item']['table']['join'] = array(
    // Index this array by the table name to which this table refers.
    'cart_bundle' => array(
      // The primary key in the referenced table.
      'left_field' => 'cbid',
      // The foreign key in this table.
      'field' => 'cbid',
    ),
  );
}

/**
 * Implements hook_views_plugins().
 *
 * Define new view display format.
 */
function tmgmt_dgt_connector_cart_views_plugins() {
  return array(
    'style' => array(
      'table_rowspan' => array(
        'title' => t('Table Rowspan'),
        'help' => t('Merge duplicate rows in group use rowspan attribute'),
        'handler' => 'TmgmtDgtConnectorCartTableRowspan',
        'theme' => 'views_view_table',
        'uses row plugin' => FALSE,
        'uses row class' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-table',
        'parent' => 'views_plugin_style_table',
      ),
    ),
  );
}
