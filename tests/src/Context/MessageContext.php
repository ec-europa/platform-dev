<?php

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\PyStringNode;
use Drupal\DrupalExtension\Context\MessageContext as DrupalExtensionMessageContext;

/**
 * Class MessageContext.
 *
 * @package Drupal\nexteuropa\Context
 */
class MessageContext extends DrupalExtensionMessageContext {

  /**
   * Checks if the current page contains the given error message.
   *
   * @param \Behat\Gherkin\Node\PyStringNode $message
   *   PyStringNode containing the text to be checked.
   *
   * @Then I should see this following error message:
   */
  public function iShouldSeeThisFollowingErrorMessage(PyStringNode $message) {
    // Implode PyStringNode item because assertErrorVisible make its test
    // on the text cleaned of its HTML tags.
    $message_to_test = implode(' ', $message->getStrings());
    parent::assertErrorVisible($message_to_test);
  }

}
