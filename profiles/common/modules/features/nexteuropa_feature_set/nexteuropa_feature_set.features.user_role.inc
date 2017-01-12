<?php
/**
 * @file
 * nexteuropa_feature_set.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function nexteuropa_feature_set_user_default_roles() {
  $roles = array();

  // Exported role: cem.
  $roles['cem'] = (object) array(
    'name' => 'cem',
    'weight' => 5,
  );

  return $roles;
}
