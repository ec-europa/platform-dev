<?php
/**
 * @file
 * Contains Drupal\nexteuropa\Context\EuropaTheme\MessageContext.
 */

namespace Drupal\nexteuropa\Context\EuropaTheme;

use Drupal\nexteuropa\Context\MessageContext as NextEuropaMessageContext;

/**
 * Context with Drupal message management specific to Europa theme.
 */
class MessageContext extends NextEuropaMessageContext {

  protected $frontMessageSelector = 'div.ecl-messages > div.item-list > ul.ecl-message--body > li';
  protected $frontErrorMessageSelector = 'div.ecl-messages.error.alert > div.item-list > ul.ecl-message--body > li';
  protected $frontSuccessMessageSelector = 'div.ecl-messages.status.alert > div.item-list > ul.ecl-message--body > li';
  protected $frontWarningMessageSelector = 'div.ecl-messages.warning.alert > div.item-list > ul.ecl-message--body > li';

  /**
   * MessageContext constructor.
   *
   * @param string $front_message_selector
   *    The message css selector.
   * @param string $front_error_message_selector
   *    The error message css selector.
   * @param string $front_success_message_selector
   *    The success message css selector.
   * @param string $front_warning_message_selector
   *    The warning message css selector.
   */
  public function __construct($front_message_selector, $front_error_message_selector, $front_success_message_selector, $front_warning_message_selector) {
    if (!empty($front_message_selector)) {
      $this->frontMessageSelector = $front_message_selector;
    }

    if (!empty($front_error_message_selector)) {
      $this->frontErrorMessageSelector = $front_error_message_selector;
    }

    if (!empty($front_success_message_selector)) {
      $this->frontSuccessMessageSelector = $front_success_message_selector;
    }

    if (!empty($front_warning_message_selector)) {
      $this->frontWarningMessageSelector = $front_warning_message_selector;
    }
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertErrorVisible($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertErrorVisible($message);
    }
    else {
      $this->assert(
        $message,
        $this->frontErrorMessageSelector,
        "The page '%s' does not contain any error messages",
        "The page '%s' does not contain the error message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertNotErrorVisible($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertNotErrorVisible($message);
    }
    else {
      $this->assertNot(
        $message,
        $this->frontErrorMessageSelector,
        "The page '%s' contains the error message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertSuccessMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertSuccessMessage($message);
    }
    else {
      $this->assert(
        $message,
        $this->frontSuccessMessageSelector,
        "The page '%s' does not contain any success messages",
        "The page '%s' does not contain the success message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertNotSuccessMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertNotSuccessMessage($message);
    }
    else {
      $this->assertNot(
        $message,
        $this->frontSuccessMessageSelector,
        "The page '%s' contains the success message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertWarningMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertWarningMessage($message);
    }
    else {
      $this->assert(
        $message,
        $this->frontWarningMessageSelector,
        "The page '%s' does not contain any warning messages",
        "The page '%s' does not contain the warning message '%s'"
      );
    }
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertNotWarningMessage($message) {
    if ($this->isCurrentPageAdmin()) {
      // If it is an admin page, then the admin theme is used and the default
      // display of messages is applied.
      parent::assertNotWarningMessage($message);
    }
    else {
      $this->assertNot(
        $message,
        $this->frontWarningMessageSelector,
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
