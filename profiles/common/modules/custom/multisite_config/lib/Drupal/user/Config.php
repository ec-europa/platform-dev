<?php

/**
 * @file
 * Contains \\Drupal\\user\\Config.
 */

namespace Drupal\user;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\user.
 */
class Config extends ConfigBase {

  /**
   * Assign a specific role to a user, given its UID.
   *
   * @param string $role_name
   *    Role machine name.
   * @param string $uid
   *    User UID.
   *
   * @return bool
   *    TRUE if operation was successful, FALSE otherwise.
   */
  public function assignRoleToUser($role_name, $uid) {
    $account = user_load($uid);
    $role = user_role_load_by_name($role_name);

    if ($account && $role && !isset($account->roles[$role->rid])) {
      $roles = $account->roles + array($role->rid => $role->name);
      $account->original = clone $account;
      user_save($account, array('roles' => $roles));
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Revoke a specific role from a user, given its UID.
   *
   * @param string $role_name
   *    Role machine name.
   * @param string $uid
   *    User UID.
   *
   * @return bool
   *    TRUE if operation was successful, FALSE otherwise.
   */
  public function revokeRoleFromUser($role_name, $uid) {
    $account = user_load($uid);
    $role = user_role_load_by_name($role_name);

    if ($account && $role && isset($account->roles[$role->rid])) {
      $roles = array_diff($account->roles, array($role->rid => $role->name));
      $account->original = clone $account;
      user_save($account, array('roles' => $roles));
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Grant permissions to a specific role, if it exists.
   *
   * @param string $role
   *    Role machine name.
   * @param string $permission
   *    Permission machine name.
   * @param string $module
   *    Module name.
   *
   * @return bool
   *    TRUE if operation was successful, FALSE otherwise.
   */
  public function grantPermission($role, $permission, $module = NULL) {

    $permission_rebuilt = &drupal_static(__CLASS__ . ':' . __FUNCTION__);
    if (!$permission_rebuilt) {
      // Make sure the list of available node types is up to date.
      node_types_rebuild();
      // Reset hook_permission() cached information.
      module_implements('permission', FALSE, TRUE);
      $permission_rebuilt = TRUE;
    }

    $permissions = is_array($permission) ? $permission : array($permission);
    $role_object = user_role_load_by_name($role);
    if ($role_object) {

      // Use code from user_role_grant_permissions() in order to be able
      // to force medule field in special cases.
      $modules = user_permission_get_modules();
      // Grant new permissions for the role.
      foreach ($permissions as $name) {
        $modules[$name] = isset($modules[$name]) ? $modules[$name] : $module;
        db_merge('role_permission')
          ->key(array(
            'rid' => $role_object->rid,
            'permission' => $name,
          ))
          ->fields(array(
            'module' => $modules[$name],
          ))
          ->execute();
      }

      // Clear the user access cache.
      drupal_static_reset('user_access');
      drupal_static_reset('user_role_permissions');
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Revoke permissions to a specific role, if it exists.
   *
   * @param string $role
   *    Role machine name.
   * @param string $permission
   *    Permission machine name.
   *
   * @return bool
   *    TRUE if operation was successful, FALSE otherwise.
   */
  public function revokePermission($role, $permission) {
    $role_object = user_role_load_by_name($role);
    if ($role_object) {
      user_role_revoke_permissions($role_object->rid, array($permission));
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Create user role, given its name and weight.
   *
   * @param string $name
   *    Role machine name.
   * @param int $weight
   *    Role weight.
   *
   * @return object
   *    Role object.
   */
  public function createRole($name, $weight = 0) {
    $role = new \stdClass();
    $role->name = $name;
    $role->weight = $weight;
    user_role_save($role);
    return $role;
  }

}
