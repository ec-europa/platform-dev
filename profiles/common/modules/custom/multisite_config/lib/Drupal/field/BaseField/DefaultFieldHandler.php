<?php

namespace Drupal\field\BaseField;
use Drupal\field\FieldHandlerInterface;

/**
 * Class DefaultFieldHandler.
 *
 * This default class deals with common field base settings, typically those
 * accessible at the root level if the field instance array.
 *
 * @package Drupal\field\BaseField.
 */
class DefaultFieldHandler implements FieldHandlerInterface {

  /**
   * Base field settings as required by field_create_instance().
   *
   * @var array
   */
  protected $field = array();

  /**
   * Create a base field, given its name and type.
   *
   * @param string $field_name
   *    Field machine name.
   * @param string $type
   *    Field type, as specified by hook_field_info() implementations.
   */
  public function __construct($field_name, $type) {
    $this->field = array(
      'field_name' => $field_name,
      'type' => $type,
    );

    return $this;
  }

  /**
   * Return field array built using field handler methods.
   *
   * @return array
   *    Field settings array.
   */
  public function getField() {
    return $this->field;
  }

  /**
   * Create field instance using constructed instance array.
   *
   * @return array
   *    Field array as returned by Field API CRUD operations.
   */
  public function save() {
    return field_create_field($this->field);
  }

}
