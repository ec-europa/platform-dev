<?php

namespace Drupal\multisite_config;

/**
 * Class ConfigBase.
 *
 * @package Drupal\multisite_config.
 */
class ConfigBase {

  /**
   * Call a method dynamically.
   *
   * @param string $method
   *    Method name.
   * @param mixed $args
   *    Array of arguments to be passed to the invoked method.
   *
   * @return mixed
   *    Method execution result.
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

