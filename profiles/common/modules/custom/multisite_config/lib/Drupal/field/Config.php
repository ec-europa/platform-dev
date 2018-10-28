<?php

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
   *   Field machine name.
   * @param string $type
   *   Field type, as specified by hook_field_info() implementations.
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
   *   Machine name of an existing base field.
   * @param string $entity_type
   *   Entity type machine name.
   * @param string $bundle
   *   Bundle machine name.
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
   *   Machine name of an existing base field.
   * @param string $entity_type
   *   Entity type machine name.
   * @param string $bundle
   *   Bundle machine name.
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
   *   Field machine name.
   */
  public function enableFieldTranslation($field_name) {
    $info = field_info_field($field_name);
    $info['translatable'] = TRUE;
    field_update_field($info);
  }

  /**
   * Create the field base definition of the 'title_field'.
   *
   * If the field base already exist, it returns directly the field base info.
   *
   * @return array
   *   The $field array with field base info.
   */
  public function createTitleField() {
    if ($field = field_info_field('title_field')) {
      return $field;
    }

    // Exported field_base: 'title_field'.
    $title_field_base = array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'title_field',
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 1,
      'module' => 'text',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'max_length' => 255,
      ),
      'translatable' => 1,
      'type' => 'text',
    );

    return field_create_field($title_field_base);
  }

}
