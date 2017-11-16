<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\DatabaseLogContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use function \bovigo\assert\assert;
use function \bovigo\assert\predicate\isOfType;
use function \bovigo\assert\predicate\matches;
use function \bovigo\assert\predicate\isNotOfType;

/**
 * Context for assertions related to logging.
 */
class DatabaseLogContext implements Context {

  /**
   * Assert that a specific error is logged.
   *
   * @Then an error is logged with type :arg1 and a message matching :arg2
   */
  public function anErrorIsLogged($arg1, $arg2) {
    $this->assertMessageLogged(WATCHDOG_ERROR, $arg1, $arg2);
  }

  /**
   * Assert that a specific critical message is logged.
   *
   * @Then a critical error message is logged with type :arg1 and a message matching :arg2
   */
  public function aCriticalErrorMessageIsLogged($arg1, $arg2) {
    $this->assertMessageLogged(WATCHDOG_CRITICAL, $arg1, $arg2);
  }

  /**
   * Assert that a specific informational message is logged.
   *
   * @Then an informational message is logged with type :arg1 and a message matching :arg2
   */
  public function anInfoMessageIsLogged($arg1, $arg2) {
    $this->assertMessageLogged(WATCHDOG_INFO, $arg1, $arg2);
  }

  /**
   * Assert that a specific informational message is not logged.
   *
   * @Then no informational message is logged with type :arg1 and a message matching :arg2
   */
  public function noInfoMessageIsLogged($arg1, $arg2) {
    $this->assertMessageNotLogged(WATCHDOG_INFO, $arg1, $arg2);
  }

  /**
   * Assert that a specific message is logged.
   *
   * @param int $severity
   *   The severity of the message.
   * @param string $type
   *   The type (category) of the message.
   * @param string $message
   *   A regular expression pattern the message needs to match.
   *
   * @see watchdog()
   */
  protected function assertMessageLogged($severity, $type, $message) {
    $log = $this->getLogMessages($severity, $type);

    assert($log, isOfType('object'));

    $full_message = strtr($log->message, unserialize($log->variables));

    assert($full_message, matches('@' . $message . '@'));
  }

  /**
   * Assert that a specific message is not logged.
   *
   * @param int $severity
   *   The severity of the message.
   * @param string $type
   *   The type (category) of the message.
   * @param string $message
   *   A regular expression pattern the message needs to match.
   *
   * @see watchdog()
   */
  protected function assertMessageNotLogged($severity, $type, $message) {
    $log = $this->getLogMessages($severity, $type);

    assert($log, isNotOfType('object'));
  }

  /**
   * Gets the latest watchdog message of a specific severity and type.
   *
   * @param int $severity
   *   The severity level of the message to retrieve.
   * @param string $type
   *   The type (category) of the message to retrieve.
   *
   * @return \stdClass|bool
   *   The object containing log message attributes; otherwise FALSE.
   */
  private function getLogMessages($severity, $type) {
    $query = db_select('watchdog', 'w');
    $query
      ->fields('w', array('message', 'variables'))
      ->condition('severity', $severity)
      ->condition('type', $type);

    $query->orderBy('timestamp', 'DESC');

    $result = $query->execute();
    return $result->fetchObject();
  }

}
