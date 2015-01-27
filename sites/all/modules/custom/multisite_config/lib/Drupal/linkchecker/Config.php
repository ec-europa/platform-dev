<?php

/**
 * @file
 * Contains \Drupal\linkchecker\Config
 */

namespace Drupal\linkchecker;

use Drupal\multisite_config\ConfigBase;

class Config extends ConfigBase {

  /**
   * Enable Linkchecker control on a specific content type.
   *
   * @param type $content_type
   *    Content type machine name.
   */
  public function enableLinkcheckerForContentType($content_type) {
    $settings = variable_get('linkchecker_scan_nodetypes', array());
    $settings[$content_type] = $content_type;
    variable_set('linkchecker_scan_nodetypes', $settings);
  }

  /**
   *
   * @param type $content_type
   */
  public function disableLinkcheckerForContentType($content_type) {
    $settings = variable_get('linkchecker_scan_nodetypes', array());
    $settings[$content_type] = 0;
    variable_set('linkchecker_scan_nodetypes', $settings);
  }

} 
