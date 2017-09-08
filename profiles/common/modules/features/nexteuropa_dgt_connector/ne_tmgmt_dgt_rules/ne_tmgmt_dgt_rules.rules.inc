<?php
/**
 * @file
 * Next Europa TMGMT DGT Rules module file.
 */

/**
 * Implements hook_rules_file_info().
 */
function ne_tmgmt_dgt_rules_rules_file_info() {
  $items = array();
  $items[] = 'ne_tmgmt_dgt_rules.rules';

  return $items;
}

/**
 * Implements hook_rules_condition_info().
 */
function ne_tmgmt_dgt_rules_rules_condition_info() {
  $items = array();

  $items['comparison_of_moderation_states_after_transition'] = array(
    'group' => t("NE DGT Rules"),
    'label' => t("Comparison of moderation states after transition"),
    'base' => 'ne_tmgmt_dgt_rules_comparison_of_moderation_states_after_transition',
    'parameter' => array(
      'previous_state_source' => array(
        'type' => 'text',
        'label' => t("The 'previous' moderation state value source"),
        'description' => t("Select the source of the 'previous' moderation state value."),
        'restriction' => 'selector',
      ),
      'previous_state_value' => array(
        'type' => 'text',
        'label' => t("Expected 'previous' moderation state"),
        'description' => t("Select the 'previous' workbench moderation state from the drop down list."),
        'options list' => 'workbench_moderation_state_labels',
        'restriction' => 'input',
        'save' => TRUE,
      ),
      'new_state_source' => array(
        'type' => 'text',
        'label' => t("The 'new' moderation state source"),
        'description' => t("Select the source of the 'new' moderation state value."),
        'restriction' => 'selector',
      ),
      'new_state_value' => array(
        'type' => 'text',
        'label' => t("Expected new moderation state"),
        'description' => t("Select the 'new' workbench moderation state from the drop down list."),
        'options list' => 'workbench_moderation_state_labels',
        'restriction' => 'input',
        'save' => TRUE,
      ),
    ),
    'access callback' => 'rules_node_integration_access',
  );

  return $items;
}

/**
 * Condition: Compare moderation states after transition.
 *
 * @param string $previous_state_source
 *   The 'previous' workbench moderation state value source.
 * @param string $previous_state_value
 *   Expected 'previous' workbench moderation state value.
 * @param string $new_state_source
 *   The 'new' workbench moderation state value source.
 * @param string $new_state_value
 *   Expected 'new' workbench moderation state value.
 *
 * @return TRUE/FALSE
 *  TRUE/FALSE depending on if the states matches source and selected values.
 */
function ne_tmgmt_dgt_rules_comparison_of_moderation_states_after_transition($previous_state_source, $previous_state_value, $new_state_source, $new_state_value) {
  if (($previous_state_source === $previous_state_value) && ($new_state_source === $new_state_value)) {
    return TRUE;
  }

  return FALSE;
}
