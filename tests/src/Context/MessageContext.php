<?php
/**
 * Created by PhpStorm.
 * User: udongil
 * Date: 06/12/2016
 * Time: 11:48
 */

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\PyStringNode;
use Drupal\DrupalExtension\Context\MessageContext as DrupalExtensionMessageContext;

class MessageContext extends DrupalExtensionMessageContext {
  /**
   * @Then I should see this following error message:
   */
  public function iShouldSeeThisFollowingErrorMessage(PyStringNode $string) {
    print_r($string, TRUE);
    $raw_string = $string->getRaw();
    $string_to_test = implode(' ', $string->getStrings());
    print_r($string_to_test, TRUE);
    $selector = $this->getDrupalSelector('error_message_selector');
    $selectorObjects = $this->getSession()->getPage()->findAll("css", $selector);
    if (empty($selectorObjects)) {
      print_r('NO selector object found');
    }
    foreach ($selectorObjects as $selectorObject) {
      print_r('text: ' .$selectorObject->getText());
    }
    parent::assertErrorVisible($string_to_test);
  }

}