<?php
/**
 * @file
 * Next Europa DGT Rules integration - Custom actions.
 */

/**
 * Implements hook_rules_event_info().
 */
function ne_tmgmt_dgt_ftt_translator_rules_event_info() {
  return array(
    'ftt_translation_received' => array(
      'label' => t('FTT Translation received'),
      'module' => 'DGT FTT translator',
      'group' => 'DGT FTT translator',
      'variables' => array(
        'identifier' => array('type' => 'struct', 'label' => t('Poetry request identifier.')),
      ),
    ),
  );
}
