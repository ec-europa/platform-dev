<?php

/**
 * @file
 * Documentation file for the module API.
 */

/**
 * Acts on the list of user data value to save of the Ecas user.
 *
 * @param object $user
 *   A user object.
 * @param array $user_info
 *   An associative array with user data coming from EU login.
 *   These values will be used to fill fields of the user's profiles.
 * @param array $edit
 *   The list array of user data values. it is the same "$edit" parameter as
 *   in user_save().
 * @param array $args
 *   Extra parameters linked directly to the drupal-Ecas login process.
 */
function hook_ecas_sync_user_info($user, array $user_info, array &$edit, array $args) {
  $role = user_role_load_by_name('role_name');
  $user_roles = (isset($user->roles)) ? $user->roles : array();
  $user_roles[$role->rid] = $role->name;

  $edit['roles'] = $user_roles;
}

/**
 * Alters the Ecas user roles before saving it.
 *
 * @param array $user_roles
 *   The array of user roles already set.
 * @param object $user
 *   The user related to the roles to alter.
 * @param array $user_info
 *   An associative array with user data coming from EU login.
 * @param array $args
 *   Extra parameters linked directly to the drupal-Ecas login process.
 */
function hook_ecas_user_roles_alter(array &$user_roles, $user, array $user_info, array $args) {
  $user_department = ecas_get_user_department($user_info);

  if (empty($user_department['dg'])) {
    return;
  }

  $dg_id = $user_department['dg'];

  // Mapping between DG and drupal roles.
  $rules = ecas_group_sync_get_ecas_sync_rules($dg_id, 'role');

  if (!$rules) {
    return;
  }

  foreach ($rules as $rule) {
    $user_roles[$rule->synctype_value] = $rule->name;
  }
}

/**
 * Responds to the synchronisation of the ECAS user.
 *
 * This hook is invoked from ecas_sync_user_info() after the user object has
 * been defined saved.
 *
 * @param object $user
 *   A user object.
 * @param array $user_info
 *   An associative array with user data coming from EU login.
 *   These values will be used to fill fields of the user's profiles.
 * @param array $args
 *   Extra parameters linked directly to the drupal-Ecas login process.
 */
function hook_info_ecas_update($user, array $user_info, array $args) {
  $group_query = db_select('node', 'n')
    ->condition('title', 'group delta')
    ->fields('n', array('nid'));

  $nid = $group_query->execute()->fetchField();
  og_group('node', $nid, array(
    "entity type" => "user",
    "entity" => $user,
    "field_name" => 'og_user_node',
  ));
}
