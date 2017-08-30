<?php

/**
 * @file
 * Contains \Drupal\field_group\FieldGroupHandlerInterface.
 */

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
   * @return [a-zA-Z]+
   *   [a-zA-Z]+ array as returned by Field API CRUD operations.
   */
  public function save();

  /**
   * Return field group definition array built using handler methods.
   *
   * @return [a-zA-Z]+
   *   [a-zA-Z]+ group definition array.
   */
  public function getDefinition();

}
