<?php
/**
 * @file
 * multisite_rules_configuration.features.workbench_moderation_transitions.inc
 */

/**
 * Implements hook_workbench_moderation_export_transitions().
 */
function multisite_rules_configuration_workbench_moderation_export_transitions() {
  $items = array(
    'draft:needs_review' => array(
      'from_name' => 'draft',
      'to_name' => 'needs_review',
      // 'name' => 'draft-needs_review',
    ),
    'needs_review:draft' => array(
      'from_name' => 'needs_review',
      'to_name' => 'draft',
      // 'name' => 'needs_review-draft',
    ),
    'needs_review:published' => array(
      'from_name' => 'needs_review',
      'to_name' => 'published',
      // 'name' => 'needs_review-published',
    ),
    'needs_review:validated' => array(
      'from_name' => 'needs_review',
      'to_name' => 'validated',
      // 'name' => 'needs_review-validated',
    ),
    'published:archived' => array(
      'from_name' => 'published',
      'to_name' => 'archived',
      // 'name' => 'published-archived',
    ),
    'validated:published' => array(
      'from_name' => 'validated',
      'to_name' => 'published',
      // 'name' => 'validated-published',
    ),
  );
  return $items;
}
