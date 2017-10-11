<?php

namespace Drupal\field_group;

/**
 * Class DefaultFieldHandler.
 *
 * @package Drupal\field_group\InstanceField
 */
class FieldGroupHandler implements FieldGroupHandlerInterface {
  /**
   * Field group definition array as required by field_group_save().
   *
   * @var array
   */
  protected $definition = array();

  /**
   * Construct instance field handler with required information.
   *
   * @param string $label
   *    Field group label.
   * @param string $group_name
   *    Field group machine name.
   * @param string $entity_type
   *    Entity type machine name.
   * @param string $bundle
   *    Bundle machine name.
   */
  public function __construct($label, $group_name, $entity_type, $bundle) {
    $this->definition = new \stdClass();
    $this->definition->identifier = "$group_name|$entity_type|$bundle|form";
    $this->definition->group_name = $group_name;
    $this->definition->entity_type = $entity_type;
    $this->definition->bundle = $bundle;
    $this->definition->mode = 'form';
    $this->definition->parent_name = '';
    $this->definition->label = $label;
    $this->definition->weight = '0';
    $this->definition->children = array();
    $this->definition->format_type = '';
    $this->definition->format_settings = array();
    return $this;
  }

  /**
   * Return field array built using field handler methods.
   *
   * @return object
   *    Field settings object.
   */
  public function getDefinition() {
    return $this->definition;
  }

  /**
   * Create field group instance using internal definition array.
   *
   * @return object
   *    Field group configuration object.
   */
  public function save() {
    $service = new Config();
    $group = $service->loadFieldGroupByIdentifier($this->definition->identifier);
    if ($group) {
      foreach ($this->definition as $name => $value) {
        $group->{$name} = $this->definition->{$name};
      }
      field_group_group_save($group);
      return $group;
    }
    else {
      return field_group_group_save($this->definition);
    }
  }

  /**
   * Set field group child.
   *
   * @param string $field_name
   *    Machine name of the field belonging to the field group.
   *
   * @return $this
   */
  public function setChild($field_name) {
    $this->definition->children[] = $field_name;
    return $this;
  }

  /**
   * Set field group children.
   *
   * @param array $children
   *    Array of field machine names.
   *
   * @return $this
   */
  public function setChildren(array $children) {
    foreach ($children as $child) {
      $this->setChild($child);
    }
    return $this;
  }

  /**
   * Set field group weight.
   *
   * @param int $weight
   *    Field group weight.
   *
   * @return $this
   */
  public function setWeight($weight) {
    $this->definition->weight = $weight;
    return $this;
  }

  /**
   * Set field group format type.
   *
   * @param string $format_type
   *    Field group format type.
   *
   * @return $this
   */
  public function setType($format_type) {
    $this->definition->format_type = $format_type;
    return $this;
  }

  /**
   * Set field group format setting formatter.
   *
   * @param string $formatter
   *    Field group formatter.
   *
   * @return $this
   */
  public function setFormatter($formatter) {
    $this->definition->format_settings['formatter'] = $formatter;
    return $this;
  }

  /**
   * Set field group instance setting name and value.
   *
   * @param string $name
   *    Instance setting name.
   * @param string $value
   *    Instance setting value.
   *
   * @return $this
   */
  public function setInstanceSetting($name, $value) {
    $this->definition->format_settings['instance_settings'][$name] = $value;
    return $this;
  }

}
