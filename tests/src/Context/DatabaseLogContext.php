<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use function \bovigo\assert\assert;
use function \bovigo\assert\predicate\isOfType;
use function \bovigo\assert\predicate\matches;

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
   * Assert that a specific informational message is logged.
   *
   * @Then an informational message is logged with type :arg1 and a message matching :arg2
   */
  public function anInfoMessageIsLogged($arg1, $arg2) {
    $this->assertMessageLogged(WATCHDOG_INFO, $arg1, $arg2);
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
    $query = db_select('watchdog', 'w');
    $query
      ->fields('w', array('message', 'variables'))
      ->condition('severity', $severity)
      ->condition('type', $type);

    $query->orderBy('timestamp', 'DESC');

    $result = $query->execute();
    $log = $result->fetch();

    assert($log, isOfType('object'));

    $full_message = strtr($log->message, unserialize($log->variables));

    assert($full_message, matches('@' . $message . '@'));
  }

}
