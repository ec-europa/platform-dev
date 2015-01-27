<?php

/**
 * @file
 * Contains \Drupal\features\Config
 */

namespace Drupal\features;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * @param $feature_name
   * @param $components
   */
  public function revertComponents($feature_name, $components) {
    $components = !is_array($components) ? array($components) : $components;
    features_revert(array($feature_name => $components));
  }

}
