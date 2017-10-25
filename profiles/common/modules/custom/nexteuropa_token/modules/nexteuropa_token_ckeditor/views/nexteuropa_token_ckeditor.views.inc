<?php

/**
 * @file
 * Expose hook_views_data_alter() implementations.
 */

/**
 * Implements hook_views_data_alter().
 */
function nexteuropa_token_ckeditor_views_data_alter(&$data) {
  foreach (entity_get_info() as $entity_type => $info) {
    if (isset($info['base table']) && isset($data[$info['base table']]['table'])) {
      $data[$info['base table']]['nexteuropa_token_ckeditor_widget_selection'] = array(
        'title' => $data[$info['base table']]['table']['group'],
        'group' => t('CKEditor selection'),
        'help' => t('Provide a widget to select view modes tokens exposed by NextEuropa Token module, to be used only on CKEditor Token filter views.'),
        'real field' => $info['entity keys']['id'],
        'field' => array(
          'handler' => 'nexteuropa_token_ckeditor_handler_field_selection',
          'click sortable' => FALSE,
        ),
      );
      $data[$info['base table']]['nexteuropa_token_ckeditor_bean_widget_selection'] = array(
        'title' => $data[$info['base table']]['table']['group'],
        'group' => t('CKEditor selection'),
        'help' => t('Provide a widget to select view modes tokens exposed by NextEuropa Token module, to be used only on CKEditor Token filter views.'),
        'real field' => $info['entity keys']['id'],
        'field' => array(
          'handler' => 'nexteuropa_token_ckeditor_bean_handler_field_selection',
          'click sortable' => FALSE,
        ),
      );
    }
    if (isset($info['revision table']) && isset($data[$info['revision table']]['table'])) {
      $data[$info['revision table']]['nexteuropa_token_ckeditor_widget_selection'] = array(
        'title' => $data[$info['revision table']]['table']['group'],
        'group' => t('CKEditor selection'),
        'help' => t('Provide a widget to select view modes tokens exposed by NextEuropa Token module, to be used only on CKEditor Token filter views.'),
        'real field' => $info['entity keys']['revision'],
        'field' => array(
          'handler' => 'nexteuropa_token_ckeditor_handler_field_selection',
          'click sortable' => FALSE,
        ),
      );
      $data[$info['revision table']]['nexteuropa_token_ckeditor_bean_widget_selection'] = array(
        'title' => $data[$info['revision table']]['table']['group'],
        'group' => t('CKEditor selection'),
        'help' => t('Provide a widget to select view modes tokens exposed by NextEuropa Token module, to be used only on CKEditor Token filter views.'),
        'real field' => $info['entity keys']['revision'],
        'field' => array(
          'handler' => 'nexteuropa_token_ckeditor_bean_handler_field_selection',
          'click sortable' => FALSE,
        ),
      );
    }
  }
}
