<?php

/**
 * @file
 * Contains \\Drupal\\field_group\\Config.
 */

namespace Drupal\field_group;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\field_group
 */
class Config extends ConfigBase {

  /**
   * Returns a field group handler object instance.
   *
   * The field group handler provides methods to build a field group definition
   * array, which will need to be saved by calling its save() method.
   *
   * @param string $label
   *    Field group label.
   * @param string $group_name
   *    Field group machine name.
   * @param string $entity_type
   *    Entity type machine name.
   * @param string $bundle
   *    Bundle machine name.
   *
   * @return \Drupal\field_group\FieldGroupHandler
   *    Field group handler object instance.
   */
  public function createFieldGroup($label, $group_name, $entity_type, $bundle) {
    return new FieldGroupHandler($label, $group_name, $entity_type, $bundle);
  }

}
