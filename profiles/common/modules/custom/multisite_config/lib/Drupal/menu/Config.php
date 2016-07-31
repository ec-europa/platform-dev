<?php

namespace Drupal\menu;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\menu
 */
class Config extends ConfigBase {

  /**
   * Set available menus setting for a specific content type.
   *
   * @param string $content_type
   *    Content type machine name.
   * @param mixed $menus
   *    Menus to be available.
   */
  public function setAvailableMenusForContentType($content_type, $menus) {
    if (!is_array($menus)) {
      return;
    }

    $value = array();
    foreach ($menus as $menu) {
      $value[] = $menu;
    }

    variable_set('menu_options_' . $content_type, $value);
  }

}
