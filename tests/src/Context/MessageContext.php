<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MessageContext.
 */

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
   * @param Behat\Gherkin\Node\PyStringNode $message
   *   PyStringNode containing the text to be checked.
   *
   * @Then I should see this following error message:
   */
  public function iShouldSeeThisFollowingErrorMessage(PyStringNode $message) {
    // Implode PyStringNode item because assertErrorVisible make its test
    // on the text cleaned of its HTML tags.
    $message_to_test = implode(' ', $message->getStrings());
    $this->assertErrorVisible($message_to_test);
  }

  /**
   * {@inheritdoc}
   */
  public function assertMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertMessage($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_message_selector');
      $this->assert(
        $message,
        $selector,
        "The page '%s' does not contain any messages",
        "The page '%s' does not contain the message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function assertNotMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertNotMessage($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_message_selector');
      $this->assertNot(
        $message,
        $selector,
        "The page '%s' contains the message '%s'"
      );
    }
  }

  /**
   * Checks if the current page contains the given error message.
   *
   * @param string $message
   *   string The text to be checked.
   *
   * @Then I should see the error message( containing) :message in the Media modal
   */
  public function assertMediaErrorVisible($message) {
    parent::assertErrorVisible($message);
  }

  /**
   * Checks if the current page does not contain the given error message.
   *
   * @param string $message
   *   string The text to be checked.
   *
   * @Given I should not see the error message( containing) :message in the Media modal
   */
  public function assertMediaNotErrorVisible($message) {
    parent::assertNotErrorVisible($message);
  }

  /**
   * {@inheritdoc}
   */
  public function assertErrorVisible($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertErrorVisible($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_error_message_selector');
      $this->assert(
        $message,
        $selector,
        "The page '%s' does not contain any error messages",
        "The page '%s' does not contain the error message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function assertNotErrorVisible($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertNotErrorVisible($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_error_message_selector');
      $this->assertNot(
        $message,
        $selector,
        "The page '%s' contains the error message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function assertSuccessMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertSuccessMessage($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_success_message_selector');
      $this->assert(
        $message,
        $selector,
        "The page '%s' does not contain any success messages",
        "The page '%s' does not contain the success message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function assertNotSuccessMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertNotSuccessMessage($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_success_message_selector');
      $this->assertNot(
        $message,
        $selector,
        "The page '%s' contains the success message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function assertWarningMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertWarningMessage($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_warning_message_selector');
      $this->assert(
        $message,
        $selector,
        "The page '%s' does not contain any warning messages",
        "The page '%s' does not contain the warning message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  public function assertNotWarningMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertNotWarningMessage($message);
    }
    else {
      $selector = $this->getDrupalSelector('front_warning_message_selector');
      $this->assertNot(
        $message,
        $selector,
        "The page '%s' contains the warning message '%s'"
      );
    }
  }


  /**
   * Internal callback to check for a specific message in a given context.
   *
   * @param string $message
   *    The message to be checked.
   * @param string $selector
   *    The css selector.
   * @param string $exception_msg_none
   *    The message being thrown when no message is contained, string
   *    should contain one '%s' as a placeholder for the current URL.
   * @param string $exception_msg_missing
   *    The message being thrown when the message is not contained, string
   *    should contain two '%s' as placeholders for the current URL and the
   *    message.
   *
   * @throws \Exception
   */
  private function assert($message, $selector, $exception_msg_none, $exception_msg_missing) {
    $selector_objects = $this->getSession()->getPage()->findAll("css", $selector);
    if (empty($selector_objects)) {
      throw new \Exception(sprintf($exception_msg_none, $this->getSession()->getCurrentUrl()));
    }
    foreach ($selector_objects as $selector_object) {
      if (strpos(trim($selector_object->getText()), $message) !== FALSE) {
        return;
      }
    }
    throw new \Exception(sprintf($exception_msg_missing, $this->getSession()->getCurrentUrl(), $message));
  }

  /**
   * Checks if the current page does not contain the given message.
   *
   * @param string $message
   *    The message to be checked.
   * @param string $selector
   *    The css selector.
   * @param string $exception_msg
   *    The message being thrown when the message is contained, string
   *    should contain two '%s' as placeholders for the current URL and the
   *    message.
   *
   * @throws \Exception
   */
  private function assertNot($message, $selector, $exception_msg) {
    $selector_objects = $this->getSession()->getPage()->findAll("css", $selector);
    if (!empty($selector_objects)) {
      foreach ($selector_objects as $selector_object) {
        if (strpos(trim($selector_object->getText()), $message) !== FALSE) {
          throw new \Exception(sprintf($exception_msg, $this->getSession()->getCurrentUrl(), $message));
        }
      }
    }
  }


  /**
   * Helps to determine if the current page is an admin page.
   *
   * @return bool
   *    TRUE if it is an admin page
   */
  private function isCurrentPageAdmin() {
    $base_url = $this->getMinkParameter('base_url');
    $url = $this->getSession()->getCurrentUrl();

    // Retrieve the page path from the URL.
    $path = str_replace($base_url . '/', '', $url);

    return path_is_admin($path);
  }

}
