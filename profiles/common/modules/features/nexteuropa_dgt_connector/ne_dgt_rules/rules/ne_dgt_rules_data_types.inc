<?php
/**
 * @file
 * Next Europa DGT Rules integration - Custom data types.
 */

/**
 * Implements hook_rules_data_info().
 */
function ne_dgt_rules_rules_data_info() {
  return array(
    'dgt_service_response' => array(
      'label' => t('DGT Translation Service response'),
      'wrap' => TRUE,
      'group' => t('NE DGT Rules'),
      'property info' => _ne_dgt_rules_dgt_service_response_data_info(),
    ),
  );
}

/**
 * Provides properties definition for the 'dgt_service_response' data type.
 *
 * @return array
 *   An array with defined properties.
 */
function _ne_dgt_rules_dgt_service_response_data_info() {
  return array(
    'ref_id' => array(
      'type' => 'text',
      'label' => 'Reference number',
    ),
    'raw_xml' => array(
      'type' => 'text',
      'label' => 'Response XML',
    ),
  );
}
