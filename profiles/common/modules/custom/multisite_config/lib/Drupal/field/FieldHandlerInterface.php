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
   * @return array
   *   Field array as returned by Field API CRUD operations.
   */
  public function save();

  /**
   * Return field array built using field handler methods.
   *
   * @return array
   *   Field settings array.
   */
  public function getField();

}
