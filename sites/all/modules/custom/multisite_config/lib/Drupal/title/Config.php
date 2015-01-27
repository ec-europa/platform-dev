<?php

/**
 * @file
 * Contains \Drupal\title\Config
 */

namespace Drupal\title;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Replace title field on a given entity bundle.
   *
   * @param  $entity
   * @param  $bundle
   * @param  $field
   */
  public function replaceTitleField($entity = NULL, $bundle = NULL, $field = NULL) {
    title_field_replacement_toggle($entity, $bundle, $field);
  }
} 
