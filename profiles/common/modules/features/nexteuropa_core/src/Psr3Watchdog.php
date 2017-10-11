<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_core\Config.
 */

namespace Drupal\nexteuropa_core;

use Psr\Log\AbstractLogger;
use Psr\Log\LogLevel;

/**
 * Class Psr3Watchdog.
 *
 * @package Drupal\nexteuropa_core
 */
class Psr3Watchdog extends AbstractLogger {

  /**
   * Mapping between PSR3 log levels and Drupal watchdog log levels.
   *
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
   * Log type.
   *
   * @var string
   */
  private $type = 'PSR-3';

  /**
   * Set log type.
   *
   * @param string $type
   *    Log type.
   */
  public function setType($type) {
    $this->type = $type;
  }

  /**
   * Logs with an arbitrary level.
   *
   * @param mixed $level
   *    Log level.
   * @param string $message
   *    Log message.
   * @param array $context
   *    Log context.
   */
  public function log($level, $message, array $context = array()) {
    if (isset($context['message'])) {
      $context['message'] = htmlentities($context['message']);
    }
    $message .= "<pre>" . var_export($context, TRUE) . "</pre>";
    watchdog($this->type, $message, [], $this->map[$level]);
  }

}
