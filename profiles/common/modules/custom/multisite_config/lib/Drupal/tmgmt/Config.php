<?php

namespace Drupal\tmgmt;

use Drupal\multisite_config\ConfigBase;

/**
 * Class Config.
 *
 * @package Drupal\tmgmt.
 */
class Config extends ConfigBase {

  /**
   * Auto creates a translator from a translator plugin definition.
   *
   * @param string $plugin
   *   The machine-readable name of a translator plugin.
   */
  public function createDefaultTranslatorFromPlugin($plugin) {
    drupal_static_reset('_tmgmt_plugin_info');
    tmgmt_translator_auto_create($plugin);
  }

}
