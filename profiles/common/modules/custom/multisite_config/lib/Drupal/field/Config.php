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
   *    Field handler object instance.
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
   *    Field handler object instance.
   */
  public function createInstanceField($field_name, $entity_type, $bundle) {
    return new DefaultInstanceFieldHandler($field_name, $entity_type, $bundle);
  }

}
