<?php

namespace Drupal\field_group;

/**
 * Interface FieldGroupHandlerInterface.
 *
 * @package Drupal\field_group
 */
interface FieldGroupHandlerInterface {

  /**
   * Create field instance using constructed instance array.
   *
   * @return array
   *    Field array as returned by Field API CRUD operations.
   */
  public function save();

  /**
   * Return field group definition array built using handler methods.
   *
   * @return array
   *    Field group definition array.
   */
  public function getDefinition();

}
