<?php

/**
 * @file
 * Documentation file for the module API.
 */

/**
 * Alters the Ecas login process before performing Drupal-Ecas synchronisation.
 *
 * It is triggered just after getting the Drupal user based on the Ecas user
 * name.
 * It allows modifying the process based on Drupal user properties or fields
 * of an existing account or the Ecas user name.
 *
 * Note also that the phpCAS object is already available and instantiated with
 * the current Ecas user data.
 *
 * @param string $ecas_name
 *   The user name as defined in Ecas.
 * @param bool|object $account
 *   The Drupal user object associated to the Ecas user name or FALSE if the
 *   user is not registered in Drupal yet.
 * @param string $destination
 *   The final destination value as set at Ecas module level.
 *   This value is also by default the value stored in session,
 *   $_SESSION['ecas_goto'].
 *
 * @see user_load_by_name()
 * @see hook_ecas_sync_user_info()
 */
function hook_ecas_extra_filter_alter(&$ecas_name, &$account, &$destination) {
  if (!$account) {
    $ecas_attributes = phpCAS::getAttributes();
    $first_name = $ecas_attributes['cas:firstName'];
    $last_name = $ecas_attributes['cas:lastName'];

    $drupal_lastname = field_get_items('user', $account, 'field_lastname');
    $drupal_firstname = field_get_items('user', $account, 'field_firstname');
    if (($drupal_lastname[0]['value'] != $last_name) || ($drupal_firstname[0]['value'] != $first_name)) {
      unset($_REQUEST['destination']);
      drupal_goto('custom_error_page');
    }
  }
}

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
