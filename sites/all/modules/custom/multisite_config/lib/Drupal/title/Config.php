<?php

/**
 * @file
 * Contains \\Drupal\\title\\Config.
 */

namespace Drupal\title;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\title.
 */
class Config extends ConfigBase {

  /**
   * Replace title field on a given entity bundle.
   *
   * @param string $entity
   *    Entity type machine name.
   * @param string $bundle
   *    Bundle name.
   * @param string $field
   *    Title field to be replaced.
   */
  public function replaceTitleField($entity = NULL, $bundle = NULL, $field = NULL) {
    title_field_replacement_toggle($entity, $bundle, $field);
  }

}
