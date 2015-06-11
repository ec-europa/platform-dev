<?php

/**
 * @file
 * Contains \Drupal\field\BaseField\DefaultFieldHandler
 */

namespace Drupal\field\BaseField;

class DefaultFieldHandler {

  private $field = array();

  /**
   * Create a base field, given its name and type.
   *
   * @param string $field_name
   *    Field machine name.
   * @param string $type
   *    Field type, as specified by hook_field_info() implementations.
   *
   * @return \Drupal\field\BaseField\DefaultFieldHandler $this
   *    Current object instance.
   *
   * @throws \Exception
   * @throws \FieldException
   */
  public function __construct($field_name, $type) {
    $this->field = array(
      'field_name' => $field_name,
      'type' => $type,
    );
    return $this;
  }

  /**
   * Create base field using constructed field array.
   *
   * @return array
   *    Base field array as returned by field_create_field().
   *
   * @throws \Exception
   * @throws \FieldException
   */
  function save() {
    return field_create_field($this->field);
  }
}
