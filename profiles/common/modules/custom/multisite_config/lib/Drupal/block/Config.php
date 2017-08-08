<?php

/**
 * @file
 * Contains \\Drupal\\block\\Config.
 */

namespace Drupal\block;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\block
 */
class Config extends ConfigBase {

  /**
   * Set region for a block.
   *
   * @param string $module
   *    Module name.
   * @param string $delta
   *    Block delta.
   * @param string $region
   *    Theme region.
   * @param string $theme_name
   *    Theme machine name.
   *
   * @return mixed
   *    Query execution state.
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
