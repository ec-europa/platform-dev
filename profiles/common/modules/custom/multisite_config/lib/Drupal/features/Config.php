<?php

namespace Drupal\features;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\features.
 */
class Config extends ConfigBase {

  /**
   * Revert components from a specific feature.
   *
   * @param string $feature_name
   *   Feature machine name.
   * @param mixed $components
   *   List of components to revert.
   */
  public function revertComponents($feature_name, $components) {
    $components = !is_array($components) ? array($components) : $components;
    features_revert(array($feature_name => $components));
  }

}
