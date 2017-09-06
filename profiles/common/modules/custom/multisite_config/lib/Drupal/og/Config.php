<?php

/**
 * @file
 * Contains \\Drupal\\og\\Config.
 */

namespace Drupal\og;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\og.
 */
class Config extends ConfigBase {

  /**
   * Add a group field to the specified entity.
   *
   * @param object $entity
   *    Entity object.
   * @param string $bundle
   *    Entity bundle name.
   */
  public function createOgGroupField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_GROUP_FIELD, $entity, $bundle);
  }

  /**
   * Add a group access field to the specified entity.
   *
   * @param object $entity
   *    Entity object.
   * @param string $bundle
   *    Entity bundle name.
   */
  public function createOgAccessField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_ACCESS_FIELD, $entity, $bundle);
  }

  /**
   * Add a group audience field to the specified entity.
   *
   * @param object $entity
   *    Entity object.
   * @param string $bundle
   *    Entity bundle name.
   */
  public function createOgGroupAudienceField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    $og_field = array();
    if (module_exists('entityreference_prepopulate')) {
      $og_field = og_fields_info(OG_AUDIENCE_FIELD);
      // Enable the prepopulate behavior if the module is enabled.
      $og_field['instance']['settings']['behaviors']['prepopulate'] = array(
        'status' => TRUE,
        'action' => 'none',
        'fallback' => 'none',
        'skip_perm' => FALSE,
        'providers' => array(
          'url' => TRUE,
          'og_context' => TRUE,
        ),
      );
    }
    og_create_field(OG_AUDIENCE_FIELD, $entity, $bundle, $og_field);
  }

  /**
   * Add group_content_access field to the specified entity.
   *
   * @param object $entity
   *    Entity object.
   * @param string $bundle
   *    Entity bundle name.
   */
  public function createOgContentAccessField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_CONTENT_ACCESS_FIELD, $entity, $bundle);
  }

  /**
   * Add og_roles_permissions field to the specified entity.
   *
   * @param object $entity
   *    Entity object.
   * @param string $bundle
   *    Entity bundle name.
   */
  public function createOgDefaultContentAccessField($entity = NULL, $bundle = NULL) {
    drupal_static_reset('og_fields_info');
    og_create_field(OG_DEFAULT_ACCESS_FIELD, $entity, $bundle);
  }

  /**
   * Create a stub OG role object.
   *
   * @param string $name
   *   A name of the role.
   * @param object $entity
   *   Entity object.
   * @param string $entity_type
   *   Entity type.
   *
   * @return bool|int
   *   A stub OG role object.
   */
  public function createOgRole($name, $entity, $entity_type) {
    $role = og_role_create($name, $entity, 0, $entity_type);
    return og_role_save($role);
  }

  /**
   * Get OG role given group type, bundle and role name.
   *
   * @param string $group_type
   *    Group type.
   * @param string $group_bundle
   *    Group bundle.
   * @param string $role
   *    Role machine name.
   *
   * @return object
   *   Role object, as fetched from the database.
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
   * @param string $role_name
   *    OG role machine name.
   * @param mixed $permissions
   *    Array of permissions, each value is a permission string.
   * @param object $entity
   *   Entity object.
   * @param string $entity_type
   *   Entity type.
   * @param string $module
   *    Module machine name the permissions belong to.
   *
   * @return bool
   *   TRUE if permission granting was successful, FALSE otherwise.
   */
  public function grantOgPermissions($role_name, $permissions, $entity, $entity_type, $module = '') {

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
