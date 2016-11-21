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
    $query = db_select('watchdog', 'w');
    $query
      ->fields('w', array('message', 'variables'))
      ->condition('severity', WATCHDOG_ERROR)
      ->condition('type', $arg1);

    $query->orderBy('timestamp', 'DESC');

    $result = $query->execute();
    $log = $result->fetch();

    assert($log, isOfType('object'));

    $full_message = strtr($log->message, unserialize($log->variables));

    assert($full_message, matches('@' . $arg2 . '@'));
  }

}
