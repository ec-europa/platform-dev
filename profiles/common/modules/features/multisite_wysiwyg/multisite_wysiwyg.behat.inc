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
   *   The instanceId used by the WYSIWYG module to identify the instance.
   * @param string $modal
   *   A CSS class or the "CKEditor" string in order to select
   *   the CKEditor specific modal.
   * @param string $field_id
   *   The HTML id of the input field from which the modal dialog is called.
   *
   * @throws Exception
   *   Throws an exception if the modal dialog cannot be found.
   *
   * @return \Behat\Mink\Element\NodeElement
   *   The toolbar DOM Node.
   */
  protected function getWysiwygModalDialog($instance_id, $modal, $field_id = NULL) {
    $driver = $this->getSession()->getDriver();

    $modal_id = $modal;
    if ('ckeditor' == drupal_strtolower($modal) && $field_id) {
      // Example: cke_editor_edit-field-ne-body-und-0-value_dialog.
      $modal_id = 'cke_editor_' . $field_id . '_dialog';
    }
    $modal_element = $driver->find("//div[contains(@class, 'cke_reset_all') and contains(@class, '$modal_id')]");
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
    $field_id = $this->getFieldIdFromInputLabel($instance_id);
    $instance = $this->getWysiwygInstance($field_id);
    $this->getSession()->executeScript("$instance.insert(\"$text\");");
  }

  /**
   * Clicking buttons in the WYSIWYG editor toolbar.
   *
   * @When /^I click the "([^"]*)" button in the "([^"]*)" WYSIWYG editor$/
   */
  public function iClickTheButtonInTheWysiwygEditor($action, $instance_id) {
    $driver = $this->getSession()->getDriver();
    $field_id = $this->getFieldIdFromInputLabel($instance_id);
    $instance_id = $this->getWysiwygInstance($field_id);
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
    $field_id = $this->getFieldIdFromInputLabel($instance_id);
    $instance_id = $this->getWysiwygInstance($field_id);
    $modal_element = $this->getWysiwygModalDialog($instance_id, $modal_id, $field_id);

    // Click the action link.
    $action_test = drupal_strtolower($action);
    switch ($action_test) {
      case 'ok':
        $close_modal_link = $modal_element->find("xpath", "//a[contains(@class, 'cke_dialog_ui_button_ok')]/span[@class='cke_dialog_ui_button']");
        $close_modal_link->click();
        $driver->wait(1000, TRUE);
        break;

      case 'cancel':
        $close_modal_link = $modal_element->find("xpath", "//a[contains(@class, 'cke_dialog_ui_button_cancel']/span[@class='cke_dialog_ui_button']");
        $close_modal_link->click();
        $driver->wait(1000, TRUE);
        break;

      default:
        $link = $modal_element->find("xpath", "//a[contains(text(),'$action')]");
        $link->click();
        $driver->wait(1000, TRUE);
        break;
    }
  }

  /**
   * Checking if WYSIWYG modal dialog with given title will be visible.
   *
   * @Then /^I should see the "([^"]*)" modal dialog from the "([^"]*)" WYSIWYG editor with "([^"]*)" title$/
   */
  public function iShouldSeeTheModal($modal_id, $instance_id, $title) {
    $field_id = $this->getFieldIdFromInputLabel($instance_id);
    $instance_id = $this->getWysiwygInstance($field_id);
    $modal_element = $this->getWysiwygModalDialog($instance_id, $modal_id, $field_id);
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
    $field_id = $this->getFieldIdFromInputLabel($instance_id);
    $instance = $this->getWysiwygInstance($field_id);
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
    $field_id = $this->getFieldIdFromInputLabel($instance_id);
    $instance_id = $this->getWysiwygInstance($field_id);
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
    $field_id = $this->getFieldIdFromInputLabel($instance_id);
    $instance_id = $this->getWysiwygInstance($field_id);
    $toolbar_element = $this->getWysiwygToolbar($instance_id);
    $button = $toolbar_element->find("xpath", "//a[starts-with(@title, '$action')]");
    if (is_null($button)) {
      throw new \Exception(sprintf('Button "%s" was not found on the page %s', $action, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Sets the screen resolution used by Behat to run the scenario.
   *
   * @param int $width
   *   The screen width in px.
   * @param int $height
   *   The screen height in px.
   *
   * @Given /^I use device with "([^"]*)" px and "([^"]*)" px resolution$/
   */
  public function iUseDeviceWithAndResolution($width, $height) {
    $this->getSession()->resizeWindow((int) $width, (int) $height, 'current');
  }

  /**
   * Gets the form input id from the input element label.
   *
   * @param string $label_value
   *   The form input label text.
   *
   * @return string
   *   The form input id
   */
  protected function getFieldIdFromInputLabel($label_value) {
    $driver = $this->getSession()->getDriver();
    try {
      $input_id = $driver->getAttribute("//label[contains(text(),'$label_value')]", 'for');
      if ($input_id) {
        return $input_id;
      }
    }
    catch (Exception $e) {
      // Exceptions occurring here, have no relationship with the running test.
      // Then, it is not the right level to raise an exception.
      // The catch is nevertheless useful because exceptions could happen if
      // the label value corresponds to the input id.
      // The "echo" is inserted for debug purpose.
      echo (sprintf('NOTICE: An exception has been raised because "%s" was not found as Label.
      that means that could be an id then getFieldIdFromInputLabel will simply return the submitted label value as id.', $label_value));
    }
    // If the id is not found, the label is considered as input id and the
    // scenario step calling the function must decide what to do with the
    // returned value.
    return $label_value;
  }

}
