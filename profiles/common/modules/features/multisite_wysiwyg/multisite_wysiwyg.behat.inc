<?php

/**
 * @file
 * Contains \NextEuropaTokenSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;
/**
 * Behat step definitions for the NextEuropa Editorial module.
 */
class MultisiteWysiwygSubContext extends RawDrupalContext implements DrupalSubContextInterface {

  /**
   * The Drupal driver manager.
   *
   * @var \Drupal\DrupalDriverManager;
   */
  protected $drupal;

  /**
   * Contains the name of the currently selected iframe.
   *
   * @var string
   */
  private $iframe = NULL;

  /**
   * Constructs a NextEuropaTokenSubContext object.
   *
   * @param DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Get the instance variable to use in Javascript.
   *
   * @param string $instance_id
   *   The instanceId used by the WYSIWYG module to identify the instance.
   *
   * @throws Exception
   *   Throws an exception if the editor doesn't exist.
   *
   * @return string
   *   A Javascript expression representing the WYSIWYG instance.
   */
  protected function getWysiwygInstance($instance_id) {
    $instance = "Drupal.wysiwyg.instances['$instance_id']";

    if (!$this->getSession()->evaluateScript("return !!$instance")) {
      throw new \Exception(sprintf('The editor "%s" was not found on the page %s', $instance_id, $this->getSession()->getCurrentUrl()));
    }

    return $instance;
  }

  /**
   * Get a Mink Element representing the WYSIWYG toolbar.
   *
   * @param string $instance_id
   *   The instanceId used by the WYSIWYG module to identify the instance.
   *
   * @throws Exception
   *   Throws an exception if the toolbar can't be found.
   *
   * @return \Behat\Mink\Element\NodeElement
   *   The toolbar DOM Node.
   */
  protected function getWysiwygToolbar($instance_id) {
    $driver = $this->getSession()->getDriver();
    $toolbar_element = $driver->find("//span[@class='cke_toolbox']");
    $toolbar_element = !empty($toolbar_element) ? $toolbar_element[0] : NULL;
    if (!$toolbar_element) {
      throw new \Exception(sprintf('Toolbar for editor "%s" was not found on the page %s', $instance_id, $this->getSession()->getCurrentUrl()));
    }

    return $toolbar_element;
  }

  /**
   * Get a Mink Element representing the WYSIWYG modal dialog.
   *
   * @param string $instance_id
   *    The instanceId used by the WYSIWYG module to identify the instance.
   * @param string $modal_id
   *    CSS class for give modal dialog.
   *
   * @throws Exception
   *   Throws an exception if the modal dialog can't be found.
   *
   * @return \Behat\Mink\Element\NodeElement
   *   The toolbar DOM Node.
   */
  protected function getWysiwygModalDialog($instance_id, $modal_id) {
    $driver = $this->getSession()->getDriver();
    $modal_element = $driver->find("//div[contains(@class, 'cke_1') and contains(@class, '$modal_id')]");
    $modal_element = !empty($modal_element) ? $modal_element[0] : NULL;
    if (!$modal_element) {
      throw new \Exception(sprintf('Modal dialog for editor "%s" was not found on the page %s', $instance_id, $this->getSession()->getCurrentUrl()));
    }

    return $modal_element;
  }

  /**
   * Fills in WYSIWYG editor with specified id.
   *
   * @When /^I type "([^"]*)" in the "([^"]*)" WYSIWYG editor$/
   */
  public function iTypeInTheWysiwygEditor($text, $instance_id) {
    $instance = $this->getWysiwygInstance($instance_id);
    $this->getSession()->executeScript("$instance.insert(\"$text\");");
  }

  /**
   * Clicking buttons in the WYSIWYG editor toolbar.
   *
   * @When /^I click the "([^"]*)" button in the "([^"]*)" WYSIWYG editor$/
   */
  public function iClickTheButtonInTheWysiwygEditor($action, $instance_id) {
    $driver = $this->getSession()->getDriver();
    $instance_id = $this->getWysiwygInstance($instance_id);
    $toolbar_element = $this->getWysiwygToolbar($instance_id);

    // Click the action button.
    $button = $toolbar_element->find("xpath", "//a[starts-with(@title, '$action')]");
    $button->click();
    $driver->wait(1000, TRUE);
  }

  /**
   * Clicking links in the Next Europa Tokens modal dialog from WYSIWYG editor.
   *
   * @When /^I click the "([^"]*)" link in the "([^"]*)" modal dialog from the "([^"]*)" WYSIWYG editor$/
   */
  public function iClickTheLinkInTheModalDialog($action, $modal_id, $instance_id) {
    $driver = $this->getSession()->getDriver();
    $instance_id = $this->getWysiwygInstance($instance_id);
    $modal_element = $this->getWysiwygModalDialog($instance_id, $modal_id);
    // Click the action link.
    $link = $modal_element->find("xpath", "//a[contains(text(),'$action')]");
    $link->click();
    $driver->wait(1000, TRUE);

    // Closing modal dialog @todo: could be moved to separate step.
    $close_modal_link = $modal_element->find("xpath", "//span[@class='cke_dialog_ui_button']");
    $close_modal_link->click();
    $driver->wait(1000, TRUE);
  }

  /**
   * Checking if WYSIWYG modal dialog with given title will be visible.
   *
   * @Then /^I should see the "([^"]*)" modal dialog from the "([^"]*)" WYSIWYG editor with "([^"]*)" title$/
   */
  public function iShouldSeeTheModal($modal_id, $instance_id, $title) {
    $instance_id = $this->getWysiwygInstance($instance_id);
    $modal_element = $this->getWysiwygModalDialog($instance_id, $modal_id);
    $title_xpath = "//div[@class='cke_dialog_title']";
    $modal_title = $modal_element->find('xpath', $title_xpath)->getText();
    if ($modal_title !== $title) {
      throw new \Exception(sprintf('Modal dialog for editor "%s" with title "%s" was not found on the page %s', $instance_id, $title, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Checks if given text exist in WYSIWYG editor.
   *
   * @Then /^I should see "([^"]*)" in the "([^"]*)" WYSIWYG editor$/
   */
  public function assertContentInWysiwygEditor($text, $instance_id) {
    $instance = $this->getWysiwygInstance($instance_id);
    $content = $this->getSession()->evaluateScript("return $instance.getContent()");
    if (strpos($text, $content) === FALSE) {
      throw new \Exception(sprintf('The text "%s" was not found in the "%s" WYSWIYG editor on the page %s', $text, $instance_id, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Checks if given button is not available in WYSIWYG editor toolbar.
   *
   * @Then /^I should not see the "([^"]*)" button in the "([^"]*)" WYSIWYG editor$/
   */
  public function iShouldNotSeeButtonInToolbar($action, $instance_id) {
    $instance_id = $this->getWysiwygInstance($instance_id);
    $toolbar_element = $this->getWysiwygToolbar($instance_id);
    $button = $toolbar_element->find("xpath", "//a[starts-with(@title, '$action')]");
    if (!is_null($button)) {
      throw new \Exception(sprintf('Button "%s" was found on the page %s', $action, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Checks if given button is available in WYSIWYG editor toolbar.
   *
   * @Then /^I should see the "([^"]*)" button in the "([^"]*)" WYSIWYG editor$/
   */
  public function iShouldSeeButtonInToolbar($action, $instance_id) {
    $instance_id = $this->getWysiwygInstance($instance_id);
    $toolbar_element = $this->getWysiwygToolbar($instance_id);
    $button = $toolbar_element->find("xpath", "//a[starts-with(@title, '$action')]");
    if (is_null($button)) {
      throw new \Exception(sprintf('Button "%s" was not found on the page %s', $action, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Switch frames inside the media dialogs.
   *
   * @When I switch to the frame :frame
   */
  public function iSwitchToTheFrame($frame) {
    $this->getSession()->switchToIFrame($frame);
    $this->iframe = $frame;
  }

  /**
   * Click on an element inside a WYSIWYG dialog.
   *
   * @When I click the :cssSelector element in the :instanceId WYSIWYG editor
   */
  public function iClickTheElementInTheWysiwygEditor($css_elector, $instance_id) {
    $instance = $this->getWysiwygInstance($instance_id);
    $editor_type = $this->getSession()->evaluateScript("return $instance.editor");

    // TODO: This is tinyMCE specific. We should probably do a switch statement
    // based on $editorType.
    $editor_iframe_id = $instance_id . '_ifr';

    // This Javascript only works on Chrome - not Firefox.
    $javascript  = "jQuery('#{$editor_iframe_id}').each(function() {";
    $javascript .= "  jQuery('{$css_elector}', this.contentWindow.document || this.contentDocument).click();";
    $javascript .= "});";

    $this->getSession()->executeScript($javascript);
  }

  /**
   * Click some text in the page.
   *
   * @When /^I click on the text "([^"]*)"$/
   */
  public function iClickOnTheText($text) {
    $session = $this->getSession();
    $element = $session->getPage()->find(
      'xpath',
      $session->getSelectorsHandler()->selectorToXpath('xpath', '*//*[text()="' . $text . '"]')
    );
    if (NULL === $element) {
      throw new \InvalidArgumentException(sprintf('Cannot find text: "%s"', $text));
    }

    $element->click();
  }

  /**
   * Close all dialog boxes and return to the node.
   *
   * @When I switch out of all frames
   */
  public function iSwitchOutOfAllFrames() {
    $this->getSession()->switchToIFrame();
    $this->iframe = NULL;
  }

  /**
   * Check that a given text exists in a given tag in a given region.
   *
   * @Then I should see :text in the :tag element in the :region region
   */
  public function assertRegionElementText($text, $tag, $region) {
    $region_obj = $this->getRegion($region);
    $elements = $region_obj->findAll('css', $tag);
    if (empty($elements)) {
      throw new \Exception(sprintf('The element "%s" was not found in the "%s" region on the page %s', $tag, $region, $this->getSession()->getCurrentUrl()));
    }

    $found = FALSE;
    foreach ($elements as $element) {
      if ($element->getText() == $text) {
        $found = TRUE;
        break;
      }
    }
    if (!$found) {
      throw new \Exception(sprintf('The text "%s" was not found in the "%s" element in the "%s" region on the page %s', $text, $tag, $region, $this->getSession()->getCurrentUrl()));
    }
  }


  /**
   * Wait for the given number of seconds.
   *
   * @When (I )wait( for) :seconds second(s)
   */
  public function iWaitForSeconds($seconds) {
    sleep($seconds);
  }

  /**
   * Click on a button which is in fact a link with CSS.
   *
   * @When I click the fake :text button
   */
  public function iClickTheFakeButton($text) {
    // Media style selector "buttons" are A tags with no href, so not findable
    // by normal steps.
    $driver = $this->getSession()->getDriver();
    $buttons = $driver->find("//a[text()='$text']");
    $buttons[0]->click();
  }

}
