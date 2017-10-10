<?php
/**
 * @file
 * Next Europa DGT Rules integration - Custom conditions.
 */

/**
 * Implements hook_rules_condition_info().
 */
function ne_dgt_rules_rules_condition_info() {
  $items = array();

  $items['content_meets_requirements_for_dgt_ftt_translator'] = array(
    'group' => t("Next Europa DGT Rules"),
    'label' => t("Content meets requirements of the DGT FTT workflow"),
    'base' => 'ne_dgt_rules_content_meets_requirements_for_dgt_ftt_workflow',
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t("Content"),
        'restriction' => 'selector',
      ),
    ),
  );

  $items['comparison_of_moderation_states_after_transition'] = array(
    'group' => t("Next Europa DGT Rules"),
    'label' => t("Comparison of moderation states after transition"),
    'base' => 'ne_dgt_rules_comparison_of_moderation_states_after_transition',
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
        'label' => t("Expected 'new' moderation state"),
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
 * Condition: Check if content meets requirements.
 *
 * @param object $node
 *   Node object.
 *
 * @return TRUE/FALSE
 *  TRUE/FALSE depending on if the content meets requirements or not.
 */
function ne_dgt_rules_content_meets_requirements_for_dgt_ftt_workflow($node) {
  // Checking if given content is integrated with the DGT FTT workflow.
  if (!variable_get('ne_dgt_rules_ftt_workflow_' . $node->type, FALSE)) {
    return FALSE;
  }

  // Checking if given content supports the entity translation mechanism.
  if (!entity_translation_node_supported_type($node->type)) {
    watchdog(
      'ne_dgt_rules',
      "Content type '$node->type' does not support the entity translation mechanism.
        It can not be used in the DGT FTT workflow. Please disable DGT FTT integration
        or enable the entity translation for given content type.",
      array(),
      WATCHDOG_ERROR
    );

    return FALSE;
  }

  return TRUE;
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
function ne_dgt_rules_comparison_of_moderation_states_after_transition($previous_state_source, $previous_state_value, $new_state_source, $new_state_value) {
  return (($previous_state_source === $previous_state_value) && ($new_state_source === $new_state_value)) ? TRUE : FALSE;
}
