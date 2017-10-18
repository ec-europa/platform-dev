<?php

namespace Drupal\field\InstanceField;

use Drupal\field\FieldHandlerInterface;

/**
 * Class DefaultFieldHandler.
 *
 * This default class deals with common field instance settings, typically those
 * accessible at the root level if the field instance array.
 *
 * This class can be extended with child classes taking care of specific field
 * instance use cases per file type. Each child class will implement specific
 * setting handling for both widgets and formatters related to that particular
 * field type.
 *
 * @package Drupal\field\InstanceField.
 */
class DefaultFieldHandler implements FieldHandlerInterface {

  /**
   * Field instance settings as required by field_create_instance().
   *
   * @var array
   */
  protected $instance = array();

  /**
   * Construct instance field handler with required information.
   *
   * @param string $field_name
   *    Machine name of an existing base field.
   * @param string $entity_type
   *    Entity type machine name.
   * @param string $bundle
   *    Bundle machine name.
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
   * @param string $display_name
   *    Entity display machine name.
   * @param string $formatter_type
   *    Formatter type machine name.
   * @param string $label
   *    Label settings, either 'inline', 'above' or 'hidden'.
   *
   * @return \Drupal\field\InstanceField\DefaultFieldHandler $this
   *    Current object.
   */
  public function display($display_name, $formatter_type, $label = 'above') {
    $this->instance['display'][$display_name]['type'] = $formatter_type;
    if ($formatter_type != 'hidden') {
      $this->instance['display'][$display_name]['label'] = $label;
    }
    return $this;
  }

  /**
   * Return field array built using field handler methods.
   *
   * @return array
   *    Field settings array.
   */
  public function getField() {
    return $this->instance;
  }

  /**
   * Create field instance using constructed instance array.
   *
   * @return array
   *    Field array as returned by Field API CRUD operations.
   */
  public function save() {
    return field_create_instance($this->instance);
  }

}
