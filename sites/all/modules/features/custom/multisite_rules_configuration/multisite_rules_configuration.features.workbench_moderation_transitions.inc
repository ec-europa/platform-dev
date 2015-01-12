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
    ),
    'needs_review:draft' => array(
      'from_name' => 'needs_review',
      'to_name' => 'draft',
    ),
    'needs_review:published' => array(
      'from_name' => 'needs_review',
      'to_name' => 'published',
    ),
    'needs_review:validated' => array(
      'from_name' => 'needs_review',
      'to_name' => 'validated',
    ),
    'published:archived' => array(
      'from_name' => 'published',
      'to_name' => 'archived',
    ),
    'validated:published' => array(
      'from_name' => 'validated',
      'to_name' => 'published',
    ),
  );
  return $items;
}
