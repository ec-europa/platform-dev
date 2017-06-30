<?php
/**
 * Created by PhpStorm.
 * User: udongil
 * Date: 29/06/2017
 * Time: 18:08
 */

namespace Drupal\nexteuropa\Context\EuropaTheme;

use Drupal\nexteuropa\Context\MessageContext as NextEuropaMessageContext;

class MessageContext extends NextEuropaMessageContext {

  /**
   * {@inheritdoc}
   * @override
   */
  public function assertErrorVisible($message) {
    $this->_assertPath(
      $message,
      "//div[contains(@class, 'ecl-message--error')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' does not contain any error messages",
      "The page '%s' does not contain the error message '%s'"
    );
  }

  /**
   * {@inheritdoc}
   * @override
   */
  public function assertWarningMessage($message) {
    $this->_assertPath(
      $message,
      "//div[contains(@class, 'ecl-message--warning')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' does not contain any warning messages",
      "The page '%s' does not contain the warning message '%s'"
    );
  }

  /**
   * {@inheritdoc}
   * @override
   */
  public function assertSuccessMessage($message) {
    $this->_assertPath(
      $message,
      "//div[contains(@class, 'ecl-message--success')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' does not contain any success messages",
      "The page '%s' does not contain the success message '%s'"
    );
  }

  /**
   * {@inheritdoc}
   * @override
   */
  public function assertNotSuccessMessage($message) {
    $this->_assertNotPath(
      $message,
      "//div[contains(@class, 'ecl-message--success')]/p[contains(@class, 'ecl-message__body')]",
      "The page '%s' contains the success message '%s'"
    );
  }


  /**
   * Internal callback to check for a specific message in a given context.
   *
   * @param $message
   *   string The message to be checked
   * @param $selectorPath
   *   string selector xpath
   * @param $exceptionMsgNone
   *   string The message being thrown when no message is contained, string
   *   should contain one '%s' as a placeholder for the current URL
   * @param $exceptionMsgMissing
   *   string The message being thrown when the message is not contained, string
   *   should contain two '%s' as placeholders for the current URL and the message.
   * @throws \Exception
   */
  private function _assertPath($message, $selectorPath, $exceptionMsgNone, $exceptionMsgMissing) {
    $selectorObjects = $this->getSession()->getPage()->findAll("xpath", $selectorPath);
    if (empty($selectorObjects)) {
      throw new \Exception(sprintf($exceptionMsgNone, $this->getSession()->getCurrentUrl()));
    }
    foreach ($selectorObjects as $selectorObject) {
      if (strpos(trim($selectorObject->getText()), $message) !== FALSE) {
        return;
      }
    }
    throw new \Exception(sprintf($exceptionMsgMissing, $this->getSession()->getCurrentUrl(), $message));
  }

  /**
   * Internal callback to check if the current page does not contain the given message
   *
   * @param $message
   *   string The message to be checked
   * @param $selectorPath
   *   string selector xpath
   * @param $exceptionMsg
   *   string The message being thrown when the message is contained, string
   *   should contain two '%s' as placeholders for the current URL and the message.
   * @throws \Exception
   */
  private function _assertNotPath($message, $selectorPath, $exceptionMsg) {
    $selectorObjects = $this->getSession()->getPage()->findAll("xpath", $selectorPath);
    if (!empty($selectorObjects)) {
      foreach ($selectorObjects as $selectorObject) {
        if (strpos(trim($selectorObject->getText()), $message) !== FALSE) {
          throw new \Exception(sprintf($exceptionMsg, $this->getSession()->getCurrentUrl(), $message));
        }
      }
    }
  }

}