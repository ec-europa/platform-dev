<?php
/**
 * @file
 * Contains Drupal\nexteuropa\Context\EuropaThemeMessageContext.
 */

namespace Drupal\nexteuropa\Context\EuropaTheme;

use Drupal\nexteuropa\Context\MessageContext as NextEuropaMessageContext;

/**
 * Context with Drupal message management specific to Europa theme.
 */
class MessageContext extends NextEuropaMessageContext {

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertErrorVisible($message) {
    $this->assertPath(
      $message,
      "//div[contains(@class, 'ecl-message--error')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' does not contain any error messages",
      "The page '%s' does not contain the error message '%s'"
    );
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertWarningMessage($message) {
    $this->assertPath(
      $message,
      "//div[contains(@class, 'ecl-message--warning')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' does not contain any warning messages",
      "The page '%s' does not contain the warning message '%s'"
    );
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertSuccessMessage($message) {
    $this->assertPath(
      $message,
      "//div[contains(@class, 'ecl-message--success')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' does not contain any success messages",
      "The page '%s' does not contain the success message '%s'"
    );
  }

  /**
   * {@inheritdoc}
   *
   * @override
   */
  public function assertNotSuccessMessage($message) {
    $this->assertNotPath(
      $message,
      "//div[contains(@class, 'ecl-message--success')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' contains the success message '%s'"
    );
  }


  /**
   * Internal callback to check for a specific message in a given context.
   *
   * @param string $message
   *    The message to be checked.
   * @param string $selector_path
   *    The selector xpath.
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
  private function assertPath($message, $selector_path, $exception_msg_none, $exception_msg_missing) {
    $selector_objects = $this->getSession()->getPage()->findAll("xpath", $selector_path);
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
   * @param string $selector_path
   *    The selector xpath.
   * @param string $exception_msg
   *    The message being thrown when the message is contained, string
   *    should contain two '%s' as placeholders for the current URL and the
   *    message.
   *
   * @throws \Exception
   */
  private function assertNotPath($message, $selector_path, $exception_msg) {
    $selector_objects = $this->getSession()->getPage()->findAll("xpath", $selector_path);
    if (!empty($selector_objects)) {
      foreach ($selector_objects as $selector_object) {
        if (strpos(trim($selector_object->getText()), $message) !== FALSE) {
          throw new \Exception(sprintf($exception_msg, $this->getSession()->getCurrentUrl(), $message));
        }
      }
    }
  }

}
