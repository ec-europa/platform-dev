<?php

/**
 * @file
 * Contains \Drupal\og\Config
 */

namespace Drupal\og;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Add a group field to the specified entity.
   *
   * @param  $entity
   * @param  $bundle
   */
  public function createOgGroupField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_GROUP_FIELD, $entity, $bundle);
  }

  /**
   * Add a group access field to the specified entity.
   *
   * @param  $entity
   * @param  $bundle
   */
  public function createOgAccessField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_ACCESS_FIELD, $entity, $bundle);
  }

  /**
   * Add a group audience field to the specified entity.
   *
   * @param  $entity
   * @param  $bundle
   */
  public function createOgGroupAudienceField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_AUDIENCE_FIELD, $entity, $bundle);
  }

  /**
   * Add group_content_access field to the specified entity.
   *
   * @param  $entity
   * @param  $bundle
   */
  public function createOgContentAccessField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_CONTENT_ACCESS_FIELD, $entity, $bundle);
  }

  /**
   * Add og_roles_permissions field to the specified entity.
   *
   * @param  $entity
   * @param  $bundle
   */
  public function createOgDefaultContentAccessField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_DEFAULT_ACCESS_FIELD, $entity, $bundle);
  }

  /**
   * Create a stub OG role object.
   *
   * @param $name
   *   A name of the role.
   * @return bool|int
   *    A stub OG role object.
   */
  public function createOgRole($name, $entity, $entity_type) {
    $role = og_role_create($name, $entity, 0, $entity_type);
    return og_role_save($role);
  }

  /**
   * Get OG role.
   *
   * @param type $group_type
   * @param type $group_bundle
   * @param type $role
   * @return type
   */
  public function getOgRole($group_type, $group_bundle, $role) {
    return db_select('og_role', 'r')
      ->fields('r')
      ->condition('name', $role)
      ->condition('group_type', $group_type)
      ->condition('group_bundle', $group_bundle)
      ->execute()
      ->fetchObject();
  }

  /**
   * Grant OG permissions.
   *
   * @param $role_name
   *    OG role machien name.
   * @param type $permissions
   *    Array of permissions, each value is a permission string.
   * @param type $module
   *    Module machine name the permissions belong to.
   * @return boolean
   *    TRUE or FALSE.
   * @throws \Exception
   * @throws \InvalidMergeQueryException
   */
  public function grantOgPermissions($role_name, $permissions = array(), $entity, $entity_type, $module = '') {

    // Due to a race condition problem in og_role_grant_permissions()
    // when ran during in installation profile we are forced to
    // manually set permissions in the database, also specifying their module.
    $role = $this->getOgRole($entity, $entity_type, $role_name);
    if ($role) {
      foreach ($permissions as $permission) {
        db_merge('og_role_permission')
          ->key(array(
            'rid' => $role->rid,
            'permission' => $permission,
            'module' => $module,
          ))
          ->execute();
      }
      og_invalidate_cache();
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
} 
