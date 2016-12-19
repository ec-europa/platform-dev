<?php
/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MediaContext.
 */

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
   * Test the content of a unique tag with no css.
   *
   * @Then I should see :text in the :tag tag
   */
  public function iShouldSeeInTheTag($text, $tag) {
    $element = $this->mink->getSession()->getPage()->find('xpath', '//' . $tag . '[contains(text(), \'' . $text . '\')]');
    if (NULL === $element) {
      throw new \InvalidArgumentException(sprintf('Could not find "%s"', $text));
    }

  }


  /**
   * Switches to the media browser iframe.
   *
   * @Then the media browser opens
   */
  public function iEnterTheMediaBrowser() {
    $this->mink->getSession()->switchToIFrame('mediaBrowser');
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

}
