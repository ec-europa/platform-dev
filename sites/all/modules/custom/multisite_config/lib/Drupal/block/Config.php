<?php

/**
 * @file
 * Contains \Drupal\block\Config
 */

namespace Drupal\block;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Set region for a block.
   *
   * @param $module
   * @param $delta
   * @param $region
   * @param $theme_name
   * @return mixed
   */
  public function setBlockRegion($module, $delta, $region, $theme_name = NULL) {

    $theme_name = $theme_name ? $theme_name : $this->getCurrentTheme();
    $query = db_update('block')
      ->fields(array('region' => $region, 'status' => 1))
      ->condition('module', $module)
      ->condition('theme', $theme_name)
      ->condition('delta', $delta);
    return $query->execute();
  }

} 
