<?php
/**
 * @file
 * multisite_rules_configuration.features.workbench_moderation_states.inc
 */

/**
 * Implements hook_workbench_moderation_export_states().
 */
function multisite_rules_configuration_workbench_moderation_export_states() {
  $items = array(
    'archived' => array(
      'name' => 'archived',
      'label' => 'Archived',
      'description' => 'Content is not published anymore',
      'weight' => 100,
    ),
    'draft' => array(
      'name' => 'draft',
      'label' => 'Draft',
      'description' => 'Work in progress',
      'weight' => -99,
    ),
    'needs_review' => array(
      'name' => 'needs_review',
      'label' => 'Needs Review',
      'description' => 'Ready for moderation',
      'weight' => 0,
    ),
    'published' => array(
      'name' => 'published',
      'label' => 'Published',
      'description' => 'Make this version live',
      'weight' => 99,
    ),
    'validated' => array(
      'name' => 'validated',
      'label' => 'Validated',
      'description' => 'Approved by administrator',
      'weight' => 10,
    ),
  );
  return $items;
}
