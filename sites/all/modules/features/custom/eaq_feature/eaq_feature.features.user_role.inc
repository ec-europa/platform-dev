<?php
/**
 * @file
 * eaq_feature.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function eaq_feature_user_default_roles() {
  $roles = array();

  // Exported role: Eurodesk Administrator.
  $roles['eurodesk administrator'] = array(
    'name' => 'eurodesk administrator',
    'weight' => '6',
  );

  // Exported role: Eurodesk Employee.
  $roles['eurodesk employee'] = array(
    'name' => 'eurodesk employee',
    'weight' => '4',
  );

  // Exported role: Eurodesk Manager.
  $roles['eurodesk manager'] = array(
    'name' => 'eurodesk manager',
    'weight' => '5',
  );

  return $roles;
}
