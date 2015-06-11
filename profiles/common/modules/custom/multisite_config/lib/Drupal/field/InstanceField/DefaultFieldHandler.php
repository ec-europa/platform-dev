<?php

/**
 * @file
 * Contains \Drupal\field\InstanceField\DefaultFieldHandler.
 */

namespace Drupal\field\InstanceField;

/**
 * Class DefaultFieldHandler.
 *
 * @package Drupal\field\InstanceField.
 */
class DefaultFieldHandler {

  /**
   * Field instance settings as required by field_create_instance().
   * @var array
   */
  private $instance = array();

  /**
   * Construct instance field handler with required information.
   *
   * @param string $field_name
   *    Machine name of an existing base field.
   * @param string $entity_type
   *    Entity type machine name.
   * @param string $bundle
   *    Bundle machine name.
   *
   * @return \Drupal\field\InstanceField\DefaultFieldHandler $this
   *    Current object instance.
   */
  public function __construct($field_name, $entity_type, $bundle) {

    $this->instance = array(
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle,
      'required' => FALSE,
    );
    return $this;
  }

  /**
   * Set field label.
   *
   * @param string $label
   *    Field label.
   *
   * @return \Drupal\field\InstanceField\DefaultFieldHandler $this
   *    Current object.
   */
  public function label($label) {
    $this->instance['label'] = $label;
    return $this;
  }

  /**
   * Set weather the field is required or not.
   *
   * @param bool $required
   *    TRUE if required, FALSE otherwise.
   *
   * @return \Drupal\field\InstanceField\DefaultFieldHandler $this
   *    Current object.
   */
  public function required($required) {
    $this->instance['required'] = $required;
    return $this;
  }

  /**
   * Set field widget type.
   *
   * @param string $widget_type
   *    Widget type machine name.
   *
   * @return \Drupal\field\InstanceField\DefaultFieldHandler $this
   *    Current object.
   */
  public function widget($widget_type) {
    $this->instance['widget'] = array(
      'type' => $widget_type,
    );
    return $this;
  }

  /**
   * Set field widget type.
   *
   * @param $display_name
   * @param $formatter_type
   * @param $label_inline
   *
   * @return \Drupal\field\InstanceField\DefaultFieldHandler $this
   *    Current object.
   */
  public function display($display_name, $formatter_type, $label_inline = FALSE) {
    $this->instance['display'][$display_name]['type'] = $formatter_type;
    if ($formatter_type != 'hidden') {
      $this->instance['display'][$display_name]['label'] = $label_inline ? 'inline' : 'above';
    }
    return $this;
  }

  /**
   * Create field instance using constructed instance array.
   *
   * @return array
   *    Instance field array as returned by field_create_instance().
   *
   * @throws \Exception
   * @throws \FieldException
   */
  function save() {
    return field_create_instance($this->instance);
  }
}
