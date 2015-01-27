<?php

/**
 * @file
 * Contains \Drupal\multisite_config\ConfigBase.
 */

namespace Drupal\multisite_config;

use Drupal\multisite_config\ConfigBaseInterface;

class ConfigBase implements ConfigBaseInterface {

  /**
   * Call a method dynamically.
   *
   * @param $method
   * @param $args
   * @return mixed
   */
  public function __call($method, $args) {

    if (method_exists($this, $method)) {
      return call_user_func_array(array($this, $method), $args);
    }
    else {
      throw new \InvalidArgumentException(t('The required method "!method" does not exist for !class', array('!method' => $method, '!class' => get_class($this))));
    }
  }
}
