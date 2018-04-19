<?php

/**
 * @file
 * Documentation file for the module API.
 */

/**
 * Act on the list of user data value to save of the Ecas user.
 *
 * @param array $edit
 *   The list array of user data values. it is the same "$edit" parameter as
 *   in user_save().
 * @param object $user
 *   A user object.
 * @param array $user_info
 *   An associative array with the following interesting keys:
 *   - mail: mail address.
 *   - givenname: first name.
 *   - sn: last name.
 *   These values will be used to fill fields/profiles/...
 * @param array $args
 *   Extra parameters, not used directly in this function but passed to the
 *   info_ecas_update() hook.
 */
function hook_ecas_sync_user_info(array &$edit, $user, array $user_info, array $args) {
  $role = user_role_load_by_name('role_name');
  $user_roles = (isset($user->roles)) ? $user->roles : array();
  $user_roles[$role->rid] = $role->name;

  $edit['roles'] = $user_roles;
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
 *   An associative array with the following interesting keys:
 *   - mail: mail address.
 *   - givenname: first name.
 *   - sn: last name.
 *   These values will be used to fill fields/profiles/...
 * @param array $args
 *   Extra parameters, not used directly in this function but passed to the
 *   info_ecas_update() hook.
 */
function ecas_group_sync_info_ecas_update($user, array $user_info, array $args) {
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
