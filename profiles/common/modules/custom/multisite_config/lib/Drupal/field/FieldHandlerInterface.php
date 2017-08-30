<?php

/**
 * @file
 * Contains \Drupal\field\FieldHandlerInterface.
 */

namespace Drupal\field;

/**
 * Interface FieldHandlerInterface.
 *
 * @package Drupal\field.
 */
interface FieldHandlerInterface {

  /**
   * Create field instance using constructed instance array.
   *
   * @return [a-zA-Z]+
   *   [a-zA-Z]+ array as returned by Field API CRUD operations.
   */
  public function save();

  /**
   * Return field array built using field handler methods.
   *
   * @return [a-zA-Z]+
   *   [a-zA-Z]+ settings array.
   */
  public function getField();

}
