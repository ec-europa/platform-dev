<?php

namespace Drupal\field_group;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\field_group
 */
class Config extends ConfigBase {

  /**
   * Loads a group definition.
   *
   * @param string $group_name
   *   Field group machine name, it should by prepended by "group_".
   * @param string $entity_type
   *   Entity type machine name.
   * @param string $bundle_name
   *   Bundle machine name.
   * @param string $mode
   *   Field group mode.
   *
   * @return object
   *   Field group definition object.
   */
  public function loadFieldGroup($group_name, $entity_type, $bundle_name, $mode = 'form') {
    return field_group_load_field_group($group_name, $entity_type, $bundle_name, $mode);
  }

  /**
   * Loads a group definition given its identifier string.
   *
   * @param string $identifier
   *   Identifier string, like "group_group_name|node|article|form".
   *
   * @return object
   *   Field group definition object.
   */
  public function loadFieldGroupByIdentifier($identifier) {
    list($group_name, $entity_type, $bundle_name, $mode) = explode('|', $identifier);
    return $this->loadFieldGroup($group_name, $entity_type, $bundle_name, $mode);
  }

  /**
   * Returns a field group handler object instance.
   *
   * The field group handler provides methods to build a field group definition
   * array, which will need to be saved by calling its save() method.
   *
   * @param string $label
   *   Field group label.
   * @param string $group_name
   *   Field group machine name, it should by prepended by "group_".
   * @param string $entity_type
   *   Entity type machine name.
   * @param string $bundle
   *   Bundle machine name.
   *
   * @return \Drupal\field_group\FieldGroupHandler
   *   Field group handler object instance.
   */
  public function createFieldGroup($label, $group_name, $entity_type, $bundle) {
    return new FieldGroupHandler($label, $group_name, $entity_type, $bundle);
  }

  /**
   * Delete field group.
   *
   * @param string $group_name
   *   Field group machine name, it should by prepended by "group_".
   * @param string $entity_type
   *   Entity type machine name.
   * @param string $bundle_name
   *   Bundle machine name.
   * @param string $mode
   *   Field group mode.
   */
  public function deleteFieldGroup($group_name, $entity_type, $bundle_name, $mode) {
    $group = $this->loadFieldGroup($group_name, $entity_type, $bundle_name, $mode);
    ctools_include('export');
    field_group_group_export_delete($group, FALSE);
  }

  /**
   * Delete a field group given its identifier.
   *
   * @param string $identifier
   *   Identifier string, like "group_group_name|node|article|form".
   */
  public function deleteFieldGroupByIdentifier($identifier) {
    list($group_name, $entity_type, $bundle_name, $mode) = explode('|', $identifier);
    $this->deleteFieldGroup($group_name, $entity_type, $bundle_name, $mode);
  }

}
