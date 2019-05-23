<?php

namespace Drupal\nexteuropa\Context;

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Exception;

/**
 * Context with Media module related functionality.
 */
class MediaContext implements Context {

  /**
   * The Mink context.
   *
   * @var MinkContext
   */
  protected $mink;

  /**
   * Gathers other contexts we rely on, before the scenario starts.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->mink = $environment->getContext(MinkContext::class);
  }

  /**
   * Switches to the media browser iframe.
   *
   * @param string $arg1
   *   The id of the iframe in media browser.
   *
   * @Then the media browser :arg1 iframe opens
   */
  public function iEnterTheMediaBrowser($arg1) {
    $this->mink->getSession()->switchToIFrame($arg1);
  }

  /**
   * Switches back from an iframe to the main window.
   *
   * @Then the media browser closes
   */
  public function theMediaBrowserCloses() {
    $this->mink->getSession()->switchToIFrame(NULL);
    $this->mink->getSession()->wait(5000, '(!document.getElementById("mediaBrowser"))');
  }

  /**
   * Asserts the preview of a media asset field is shown.
   *
   * @Then /^(?:|I )see the "(?P<field>(?:[^"]|\\")*)" preview$/
   */
  public function assertMediaAssetFieldPreview($field) {
    $field = str_replace('\\"', '"', $field);
    $label = $this->mink->getSession()->getPage()->find('xpath', '//label[contains(text(), \'' . $field . '\')]');

    $current_element = $label;

    // Ascend back up to the div with class field-type-media.
    do {
      $current_element = $current_element->getParent();
    } while (!$current_element->hasClass('field-type-media'));

    $media_field_div = $current_element;

    $preview_thumbnail = NULL;
    $remove_button = NULL;

    // Try to find the preview thumbnail & remove button (for max. 10 seconds).
    $end = microtime(TRUE) + 10;
    do {
      if (!$preview_thumbnail) {
        $preview_thumbnail = $media_field_div->find(
          'css',
          'div.preview div.media-thumbnail'
        );
      }

      if (!$remove_button) {
        $remove_button = $media_field_div->findButton('Remove');
      }

      if (!$preview_thumbnail || !$remove_button) {
        usleep(500);
      }
    } while ((!$preview_thumbnail || !$remove_button) && microtime(TRUE) < $end);

    if (!$preview_thumbnail) {
      throw new Exception(
        sprintf(
          'Preview thumbnail for field "%s" not found.',
          $field
        )
      );
    }

    if (!$remove_button) {
      throw new Exception(
        sprintf(
          'Remove button for field "%s" not found.',
          $field
        )
      );
    }
  }

  /**
   * Add a field group in the content type view and assign fields as children.
   *
   * @param string $arg1
   *   The text in the tab to click.
   * @param string $arg2
   *   The tab  with id .
   *
   * @When I click the :arg1 in :arg2 tab
   */
  public function iClickTheInTab($arg1, $arg2) {
    $element = $this->mink->getSession()->getPage()->findById($arg2);
    if (empty($element)) {
      throw new \Exception(sprintf('No tab element found for id (%s)', $arg1));
    }
    $element = $element->findLink($arg1);
    if (empty($element)) {
      throw new \Exception(sprintf('No link element found for the text (%s)', $arg1));
    }
    $element->click();
  }

  /**
   * Submit the form with id.
   *
   * @param string $arg1
   *   Id of the form to submit.
   *
   * @Then I submit :arg1 id form
   */
  public function iSubmitIdForm($arg1) {
    $element = $this->mink->getSession()->getPage()->findById('media-internet-add-upload');
    if (empty($element)) {
      throw new \Exception(sprintf('No form with id (%s) found', $arg1));
    }
    $element->submit();
  }

  /**
   * Check the text of a field.
   *
   * @param string $arg1
   *   Id of the field to check.
   * @param string $arg2
   *   Text to find on the field.
   *
   * @Then the field :arg1 is filled with :arg2
   */
  public function theFieldIsFilledWith($arg1, $arg2) {
    $page = $this->mink->getSession()->getPage()->findField($arg1);
    if (empty($page)) {
      throw new \Exception(sprintf('No field found for id (%s)', $arg1));
    }
    if ($arg2 != $page->getValue()) {
      throw new \Exception(sprintf('No match found for the text (%s)', $arg2));
    }
  }

  /**
   * Look for an iframe by xpath.
   *
   * @Then I should see the video iframe
   */
  public function iSeeTheVideoIframe() {
    // TO DO.
  }

}
