<?php

/**
 * @file
 * Contains hook_views_data_alter() implementation.
 */

/**
 * Implements hook_views_data_alter().
 */
function nexteuropa_ief_views_widget_views_data_alter(&$data) {
  foreach (entity_get_info() as $entity_type => $info) {
    if (isset($info['base table']) && isset($data[$info['base table']]['table'])) {
      $data[$info['base table']]['nexteuropa_ief_views_widget_selection'] = array(
        'title' => $data[$info['base table']]['table']['group'],
        'group' => t('Inline Entity Form selection'),
        'help' => t('Provide a checkbox to select the row for Inline Entity Form.'),
        'real field' => $info['entity keys']['id'],
        'field' => array(
          'handler' => 'nexteuropa_ief_views_widget_handler_field_selection',
          'click sortable' => FALSE,
        ),
      );
    }
    if (isset($info['revision table']) && isset($data[$info['revision table']]['table'])) {
      $data[$info['revision table']]['nexteuropa_ief_views_widget_selection'] = array(
        'title' => $data[$info['revision table']]['table']['group'],
        'group' => t('Inline Entity Form selection'),
        'help' => t('Provide a checkbox to select the row for Inline Entity Form.'),
        'real field' => $info['entity keys']['revision'],
        'field' => array(
          'handler' => 'nexteuropa_ief_views_widget_handler_field_selection',
          'click sortable' => FALSE,
        ),
      );
    }
  }
}
