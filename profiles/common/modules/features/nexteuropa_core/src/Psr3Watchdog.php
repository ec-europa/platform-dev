<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_core\Config.
 */

namespace Drupal\nexteuropa_core;

use Psr\Log\AbstractLogger;
use Psr\Log\LogLevel;

/**
 * Class Psr3Watchdog
 *
 * @package Drupal\nexteuropa_core
 */
class Psr3Watchdog extends AbstractLogger {

  /**
   * @var array
   */
  private $map = array(
    LogLevel::EMERGENCY => WATCHDOG_EMERGENCY,
    LogLevel::ALERT => WATCHDOG_ALERT,
    LogLevel::CRITICAL => WATCHDOG_CRITICAL,
    LogLevel::ERROR => WATCHDOG_ERROR,
    LogLevel::WARNING => WATCHDOG_WARNING,
    LogLevel::NOTICE => WATCHDOG_NOTICE,
    LogLevel::INFO => WATCHDOG_INFO,
    LogLevel::DEBUG => WATCHDOG_DEBUG,
  );

  /**
   * @var string
   */
  private $type = 'PSR-3';

  /**
   * Sets the type of watchdog entries created by this Psr3Watchdog instance.
   * If not set, 'PSR-3' is used.
   *
   * @param string $type
   *   The category to which this message belongs. Can be any string, but
   *   the general practice is to use the name of the module calling watchdog().
   */
  public function setType($type) {
    $this->type = $type;
  }

  /**
   * Logs with an arbitrary level.
   *
   * @param mixed $level
   * @param string $message
   * @param array $context
   * @return null
   */
  public function log($level, $message, array $context = array()) {
    if (isset($context['message'])) {
      $context['message'] = htmlentities($context['message']);
    }
    $message .= "<pre>" . var_export($context, TRUE) . "</pre>";
    watchdog($this->type, $message, [], $this->map[$level]);
  }
}
