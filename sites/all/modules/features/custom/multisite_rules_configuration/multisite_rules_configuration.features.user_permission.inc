<?php
/**
 * @file
 * multisite_rules_configuration.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function multisite_rules_configuration_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'moderate content from needs_review to validated'.
  $permissions['moderate content from needs_review to validated'] = array(
    'name' => 'moderate content from needs_review to validated',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from published to archived'.
  $permissions['moderate content from published to archived'] = array(
    'name' => 'moderate content from published to archived',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from validated to published'.
  $permissions['moderate content from validated to published'] = array(
    'name' => 'moderate content from validated to published',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  return $permissions;
}
