<?php

/**
 * @file
 * Next Europa DGT Rules integration - Custom conditions.
 */

use Drupal\ne_dgt_rules\DgtRulesTools;
use EC\Poetry\Messages\Components\Identifier;

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

  $items['all_translations_are_received'] = array(
    'group' => t("Next Europa DGT Rules"),
    'label' => t("All translations for a content are received"),
    'base' => 'ne_dgt_rules_all_translations_are_received',
    'parameter' => array(
      'identifier' => array(
        'type' => 'struct',
        'label' => t("Translation request identifier"),
        'restriction' => 'selector',
      ),
      'excluded_langs' => array(
        'type' => 'list<text>',
        'label' => t('Excluded Languages'),
        'description' => t("Select languages that are excluded from the set to be checked."),
        'options list' => 'ne_dgt_rules_enabled_languages',
        'optional' => TRUE,
        'default mode' => 'selector',
        'save' => TRUE,
        'restriction' => 'input',
      ),
    ),
  );

  $items['received_translation_belongs_to_specified_workflow'] = array(
    'group' => t("Next Europa DGT Rules"),
    'label' => t("Received translation belongs to a specified workflow"),
    'base' => 'ne_dgt_rules_received_translation_belongs_to_specified_workflow',
    'parameter' => array(
      'dgt_ftt_workflow_code' => array(
        'type' => 'text',
        'label' => t('Workflow code'),
        'description' => t("Select a translation workflow code to apply."),
        'options list' => 'ne_dgt_rules_get_workflow_codes',
        'restriction' => 'input',
      ),
      'job' => array(
        'type' => 'tmgmt_job',
        'label' => t('Translation Job'),
        'description' => t('The translation job for which translations should be accepted.'),
      ),
    ),
  );

  return $items;
}

/**
 * Condition: Check if content meets requirements.
 *
 * @param object $node
 *   Node object.
 *
 * @return true|false
 *   Returns true or false depending if the content meets requirements or not.
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
 * @return true|false
 *   Returns true or false depending if source and state values match.
 */
function ne_dgt_rules_comparison_of_moderation_states_after_transition($previous_state_source, $previous_state_value, $new_state_source, $new_state_value) {
  return (($previous_state_source === $previous_state_value) && ($new_state_source === $new_state_value)) ? TRUE : FALSE;
}

/**
 * Condition: All translations are received for a content.
 *
 * @param Identifier $identifier
 *   The translation request identifier.
 * @param array $excluded_languages
 *   Exclude given languages from the set to be checked.
 *
 * @return true|false
 *   Returns true or false depending if all translations were received.
 */
function ne_dgt_rules_all_translations_are_received(Identifier $identifier, array $excluded_languages) {
  $jobs = DgtRulesTools::loadTmgmtJobsByReference($identifier->getFormattedIdentifier());
  /** @var TMGMTJob $job */
  foreach ($jobs as $job) {
    if (!in_array($job->target_language, $excluded_languages) && $job->getCountPending()) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Condition: A received translation belongs to a given translation workflow.
 *
 * @param string $workflow_code
 *   An expected workflow code.
 * @param \TMGMTJob $job
 *   The TMGMTJob object.
 *
 * @return bool
 *   Returns true or false depending on the result of workflow codes comparison.
 */
function ne_dgt_rules_received_translation_belongs_to_specified_workflow($workflow_code, TMGMTJob $job) {
  $trans_workflow_code = $job->settings['data']['details']['workflowCode'];
  return $trans_workflow_code === $workflow_code ? TRUE : FALSE;
}

/**
 * Returns translation workflow codes.
 *
 * @return array
 *   An array with the translation workflow codes.
 */
function ne_dgt_rules_get_workflow_codes() {
  return array(
    'STS' => 'STS',
    'OPC' => 'OPC',
  );
}
