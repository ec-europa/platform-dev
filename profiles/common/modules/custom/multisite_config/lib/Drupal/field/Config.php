<?php

/**
 * @file
 * Contains \\Drupal\\field\\Config.
 */

namespace Drupal\field;

use Drupal\multisite_config\ConfigBase;
use Drupal\field\BaseField\DefaultFieldHandler as DefaultBaseFieldHandler;
use Drupal\field\InstanceField\DefaultFieldHandler as DefaultInstanceFieldHandler;

/**
 * Class Config.
 *
 * @package Drupal\field.
 */
class Config extends ConfigBase {

  /**
   * Create a base field, given its name and type.
   *
   * @param string $field_name
   *    Field machine name.
   * @param string $type
   *    Field type, as specified by hook_field_info() implementations.
   *
   * @return \Drupal\field\BaseField\DefaultFieldHandler
   *   Field handler object instance.
   */
  public function createBaseField($field_name, $type) {
    $class = str_replace(' ', '', ucwords(str_replace('_', ' ', $type)));
    $class = "\\Drupal\\field\\BaseField\\{$class}FieldHandler";
    return class_exists($class) ? new $class($field_name, $type) : new DefaultBaseFieldHandler($field_name, $type);
  }

  /**
   * Create field instance given label, base field name, entity type and bundle.
   *
   * @param string $field_name
   *    Machine name of an existing base field.
   * @param string $entity_type
   *    Entity type machine name.
   * @param string $bundle
   *    Bundle machine name.
   *
   * @return \Drupal\field\InstanceField\DefaultFieldHandler
   *   Field handler object instance.
   */
  public function createInstanceField($field_name, $entity_type, $bundle) {
    return new DefaultInstanceFieldHandler($field_name, $entity_type, $bundle);
  }

  /**
   * Delete field instance given label, base field name, entity type and bundle.
   *
   * @param string $field_name
   *    Machine name of an existing base field.
   * @param string $entity_type
   *    Entity type machine name.
   * @param string $bundle
   *    Bundle machine name.
   */
  public function deleteInstanceField($field_name, $entity_type, $bundle) {
    if ($instance = field_info_instance($entity_type, $field_name, $bundle)) {
      field_delete_instance($instance);
    }
  }

  /**
   * Enable field translation.
   *
   * @param string $field_name
   *    Field machine name.
   */
  public function enableFieldTranslation($field_name) {
    $info = field_info_field($field_name);
    $info['translatable'] = TRUE;
    field_update_field($info);
  }

}
