<?php

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\NodeElement;
use Behat\Mink\Element\Element;
use Behat\Mink\Exception\ElementNotFoundException;
use Behat\Mink\Exception\ExpectationException;
use Behat\Mink\Selector\Xpath\Escaper;
use Drupal\DrupalExtension\Context\MinkContext as DrupalExtensionMinkContext;
use GuzzleHttp\Client;
use function bovigo\assert\predicate\equals;
use function bovigo\assert\predicate\isNotEmpty;
use function bovigo\assert\predicate\isTrue;
use function bovigo\assert\assert;

/**
 * Provides step definitions for interacting with Mink.
 */
class MinkContext extends DrupalExtensionMinkContext {

  /**
   * {@inheritdoc}
   */
  public function iAmOnHomepage() {
    $frontpage = variable_get('site_frontpage', 'node');
    $this->visitPath($frontpage);
  }

  /**
   * {@inheritdoc}
   */
  public function assertHomepage() {
    $frontpage = variable_get('site_frontpage', 'node');
    $this->assertSession()->addressEquals($this->locatePath($frontpage));
  }

  /**
   * Checks that the given list of files return a 200 OK status code.
   *
   * @param \Behat\Gherkin\Node\TableNode $files
   *   The list of files that should be downloadable, relative to the base URL.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *   Thrown when a file could not be downloaded.
   *
   * @Then the following files can be downloaded:
   */
  public function assertFilesDownloadable(TableNode $files) {
    $client = new Client();
    foreach ($files->getColumn(0) as $file) {
      if ($client->head($this->locatePath($file))->getStatusCode() != 200) {
        throw new ExpectationException("File $file could not be downloaded.");
      }
    }
  }

  /**
   * Fills in a field (input, textarea, select) inside a specific fieldset.
   *
   * @param string $fieldset_locator
   *   Fieldset id or legend.
   * @param string $field_locator
   *   Input id, name or label.
   * @param string $value
   *   The value to fill in.
   *
   * @throws ElementNotFoundException
   *   When the fieldset or field are not found.
   *
   * @When /^inside fieldset "(?P<fieldset_locator>(?:[^"]|\\")*)" (?:|I )fill in "(?P<field_locator>(?:[^"]|\\")*)" with "(?P<value>(?:[^"]|\\")*)"$/
   */
  public function fillFieldInsideFieldset($fieldset_locator, $field_locator, $value) {
    $fieldset = $this->findFieldset($fieldset_locator);

    if (!$fieldset) {
      throw new ElementNotFoundException(
        $this->getSession()->getDriver(),
        'fieldset', 'id|legend',
        $fieldset_locator
      );
    }

    $field = $fieldset->findField($field_locator);

    if (!$field) {
      throw new ElementNotFoundException(
        $this->getSession()->getDriver(),
        'form field', 'id|name|label|value|placeholder',
        $field_locator
      );
    }

    $field->setValue($value);
  }

  /**
   * Finds the closest ancestor fieldset element for a given legend.
   *
   * The "fieldset" named selector that Mink provides out of the box
   * has unexpected behavior when used on nested fieldsets. Therefore
   * this alternative.
   *
   * @param string $legend
   *   The legend of the fieldset.
   *
   * @see https://github.com/minkphp/Mink/issues/714
   */
  protected function findFieldset($legend) {
    $legend = (new Escaper())->escapeLiteral($legend);
    $legend_element = $this->getSession()
      ->getPage()
      ->find('xpath', '//legend[contains(normalize-space(string(.)), ' . $legend . ')]');

    $fieldset = NULL;
    do {
      $parent = $legend_element->getParent();

      if ($parent->getTagName() === 'fieldset') {
        $fieldset = $parent;
      }
      elseif ($parent->getTagName() === 'body') {
        break;
      }
    } while (!$fieldset);

    return $fieldset;
  }

  /**
   * Fills in a field with a multiline text.
   *
   * The only supported fields is currently a textarea.
   *
   * @When I fill :arg1 with:
   */
  public function iFillWith($arg1, PyStringNode $string) {
    $locator = array('field', $arg1);
    $items = $this->getSession()->getPage()->findAll('named', $locator);

    $item = $this->findElementMatching(
      function (NodeElement $item) {
        return $item->getTagName() === 'textarea';
      },
      $items
    );

    if (!$item) {
      throw new ElementNotFoundException(
        $this->getSession()->getDriver(),
        'textarea',
        'named',
        $locator
      );
    }

    $item->setValue($string->getRaw());
  }

  /**
   * Maximizes the browser window.
   *
   * Use this when some tests fail due to elements not being visible because
   * of a limited screen size.
   *
   * @BeforeScenario @maximizedwindow
   */
  public function maximizeBrowserWindow() {
    $this->getSession()->getDriver()->maximizeWindow();
  }

  /**
   * Set all permissions to admin role.
   *
   * @Given I update the administrator role permissions
   */
  public function iGiveAllPermToAdminRole() {
    if ($rid = variable_get('user_admin_role', 0)) {
      $perms = array();

      foreach (module_implements('permission') as $module) {
        foreach (module_invoke($module, 'permission') as $key => $perm) {
          $perms[$key] = $module;
        }
      }

      if ($perms) {
        foreach ($perms as $perm => $module) {
          $query = db_merge('role_permission');
          $query->key(array(
            'rid' => $rid,
            'permission' => $perm,
          ));
          $query->fields(array(
            'rid' => $rid,
            'permission' => $perm,
            'module' => $module,
          ));
          $query->execute();
        }
      }
    }
  }

  /**
   * Assert that a radio button is selected.
   *
   * @Then the radio button :arg1 is selected
   */
  public function assertRadioButtonIsSelected($arg1) {
    $locator = array('field', $arg1);
    $items = $this->getSession()->getPage()->findAll('named', $locator);

    $item = $this->findElementMatching(
      function (NodeElement $item) {
        return
          $item->getAttribute('type') === 'radio';
      },
      $items
    );

    if (!$item) {
      throw new ElementNotFoundException(
        $this->getSession()->getDriver(),
        'radio',
        'named',
        $locator
      );
    }

    assert($item->getValue(), equals($item->getAttribute('value')));
  }

  /**
   * Find an element matching the criteria defined by a callable.
   *
   * @param callable $matcher
   *   Callable which returns if the element matches or not.
   * @param \Behat\Mink\Element\NodeElement[] $elements
   *   Array of elements to search through.
   *
   * @return \Behat\Mink\Element\NodeElement|null
   *   The matching element, or NULL if no matching element was found.
   */
  protected function findElementMatching(callable $matcher, array $elements) {
    foreach ($elements as $element) {
      if (TRUE === $matcher($element)) {
        return $element;
      }
    }

    return NULL;
  }

  /**
   * Checks if the box is unchecked.
   *
   * @When I should not see the box :arg1 checked
   */
  public function assertBoxIsUnChecked($arg1) {
    $is_checked = $this->getSession()->getPage()->hasCheckedField($arg1);

    if ($is_checked) {
      throw new ExpectationException(sprintf('The box "%s" is not checked.', $this->getSession()));
    }
  }

  /**
   * Attempts to find and check a checkbox in a table row containing given text.
   *
   * @param string $row_text
   *   Text on the table row.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *   Throw exception if class table row was not found.
   *
   * @Given I check the box on the :row_text row
   */
  public function checkCheckboxOnTableRow($row_text) {
    $page = $this->getSession()->getPage();
    if ($checkbox = $this->getTableRow($page, $row_text)
      ->find('css', 'input[type=checkbox]')
    ) {
      $checkbox->check();
      return;
    }
    throw new ExpectationException(sprintf('Found a row containing "%s", but no "%s" link on the page %s', $row_text, $checkbox, $this->getSession()
      ->getCurrentUrl()), $this->getSession());
  }

  /**
   * Attempts to find and uncheck a checkbox in a table row with a given text.
   *
   * @param string $row_text
   *   Text on the table row.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *   Throw exception if class table row was not found.
   *
   * @Given I uncheck the box on the :row_text row
   */
  public function uncheckCheckboxOnTableRow($row_text) {
    $page = $this->getSession()->getPage();
    if ($checkbox = $this->getTableRow($page, $row_text)
      ->find('css', 'input[type=checkbox]')
    ) {
      $checkbox->uncheck();
      return;
    }
    throw new ExpectationException(sprintf('Found a row containing "%s", but no "%s" link on the page %s', $row_text, $checkbox, $this->getSession()
      ->getCurrentUrl()), $this->getSession());
  }

  /**
   * Test the content of a unique tag with no css.
   *
   * @Then I should see :text in the :tag tag
   */
  public function iShouldSeeInTheTag($text, $tag) {
    $element = $this->getSession()
      ->getPage()
      ->find('xpath', '//' . $tag . '[contains(text(), \'' . $text . '\')]');
    if (NULL === $element) {
      throw new \InvalidArgumentException(sprintf('Could not find "%s"', $text));
    }

  }

  /**
   * Checks a checkbox in a table row inside a specific fieldset.
   *
   * @param string $fieldset_locator
   *   Fieldset id or legend.
   * @param string $row_text
   *   Text on the table row.
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   *   When the fieldset or field are not found.
   * @throws \Behat\Mink\Exception\ExpectationException
   *    Throw exception if class table row was not found.
   *
   * @When /^inside fieldset "(?P<fieldset_locator>(?:[^"]|\\")*)" I check the box on the "(?P<row_text>(?:[^"]|\\")*)" row$/
   */
  public function checkCheckboxInsideFieldsetOnTableRow($fieldset_locator, $row_text) {
    $fieldset = $this->findFieldset($fieldset_locator);

    if (!$fieldset) {
      throw new ElementNotFoundException(
        $this->getSession()->getDriver(),
        'fieldset', 'id|legend',
        $fieldset_locator
      );
    }

    if ($checkbox = $this->getTableRow($fieldset, $row_text)
      ->find('css', 'input[type=checkbox]')
    ) {
      $checkbox->check();
      return;
    }
    throw new ExpectationException(sprintf('Found a row containing "%s", but no "%s" link on the page %s', $row_text, $checkbox, $this->getSession()
      ->getCurrentUrl()), $this->getSession());
  }

  /**
   * Retrieve a table row containing specified text from a given element.
   *
   * @param \Behat\Mink\Element\Element $element
   *   Mink element object.
   * @param string $search
   *   Table row text.
   *
   * @throws \Exception
   *   Throw exception if class table row was not found.
   *
   * @return \Behat\Mink\Element\NodeElement
   *   Table row node element.
   */
  public function getTableRow(Element $element, $search) {
    $rows = $element->findAll('css', 'tr');
    if (empty($rows)) {
      throw new \Exception(sprintf('No rows found on the page %s', $this->getSession()
        ->getCurrentUrl()));
    }
    /** @var \Behat\Mink\Element\NodeElement $row */
    foreach ($rows as $row) {
      if (strpos($row->getText(), $search) !== FALSE) {
        return $row;
      }
    }
    throw new \Exception(sprintf('Failed to find a row containing "%s" on the page %s', $search, $this->getSession()
      ->getCurrentUrl()));
  }

  /**
   * Compare the position from top between 2 divs by class.
   *
   * @param string $div1
   *   Class of the first div.
   * @param string $div2
   *   Class of the second div.
   *
   * @throws \Exception
   *   Throw exception if the two positions from top are different.
   *
   * @Then I check if :div1 and :div2 have the same position from top
   */
  public function checkIfTwoDivHaveSamePosition($div1, $div2) {
    $javascript1 = "return jQuery('." . $div1 . "').offset().top;";
    $result_div1 = intval($this->getSession()->evaluateScript($javascript1));

    $javascript2 = "return jQuery('." . $div2 . "').offset().top;";
    $result_div2 = intval($this->getSession()->evaluateScript($javascript2));

    assert($result_div1, equals($result_div2));
  }

  /**
   * Checks, that HTML page contains specified element with given attributes.
   *
   * @Then /^the page should contain the element with following id "(?P<text>(?:[^"]|\\")*)" and given attributes:$/
   */
  public function assertPageContainsElementWithGivenAttributes($id, TableNode $table) {
    $page = $this->getSession()->getPage();
    $element_node = $page->findById($id);
    // Checking if element with the given id exist in the current page.
    if (NULL === $element_node) {
      throw new \Exception(sprintf('Unable to find an element with the following id: "%s"', $id));
    }
    // Loading attributes from the step.
    $attribs = $table->getHash();
    // Checking if attributes of the element are equal.
    foreach ($attribs as $attrib) {
      $attrib_value = $element_node->getAttribute($attrib['Attribute']);
      if ($attrib_value != $attrib['Value']) {
        throw new \Exception(sprintf('The value "%1$s" for the "%2$s" attribute on the current page is different from the expected "%3$s"', $attrib['Value'], $attrib['Attribute'], $attrib_value));
      }
    }
  }

  /**
   * Clicks on a HTML element based on a css selector.
   *
   * @param string $selector
   *   The css selector to use.
   *
   * @Given I click the :arg1 element
   */
  public function iClickTheElement($selector) {
    $page = $this->getSession()->getPage();
    $element = $page->find('css', $selector);

    if (empty($element)) {
      throw new \Exception(sprintf('No html element found for the selector (%s)', $selector));
    }

    $element->click();
  }

  /**
   * Checks if a specified button is disabled.
   *
   * @Then the :button button is disabled
   */
  public function theButtonIsDisabled($button) {
    $element = $this->getSession()->getPage();
    $button_obj = $element->findButton($button);
    assert($button_obj, isNotEmpty(), sprintf('The button "%s" has not been found', $button));

    $disabled_attr = $button_obj->getAttribute('disabled');
    assert($disabled_attr, equals('disabled'), sprintf('The button "%s" is not disabled', $button));
  }

  /**
   * Checks that a select box is set to a given value is selected in select box.
   *
   * @Then :option is selected in the :selector options list
   */
  public function selectedOptionShouldBeSetTo($selector, $value_label) {
    $page = $this->getSession()->getPage();
    $select_box = $page->findField($selector);

    $optionField = $select_box->find('named', array(
      'option',
      $value_label,
    ));

    assert($optionField->isSelected(), isTrue(), sprintf('The selected option in "%s" is not "%s".', $selector, $value_label));
  }

  /**
   * Checks if a specified link is in a HTML element in a field display.
   *
   * @Then I should see the link :link in a :html_element in the field display (:container_selector)
   */
  public function assertLinkInElementOfField($link, $html_element, $container_selector) {
    $element = $this->getSession()->getPage();
    $field_container = $element->find('css', $container_selector);

    assert($field_container, isNotEmpty(), sprintf('The container identified by the "%s" css selector has not been found', $container_selector));

    $link_containers = $field_container->findAll('xpath', $html_element);

    assert($link_containers, isNotEmpty(), sprintf('The "%s" element has not been found in the container identified by the "%s" css selector', $html_element, $container_selector));

    foreach ($link_containers as $link_container) {
      $result = $link_container->findLink($link);
      if ($result && !$result->isVisible()) {
        throw new \Exception(sprintf("No link to '%s' in a %s", $link, $html_element));
      }
    }

    assert($result, isNotEmpty(), sprintf("No link to '%s' in a %s", $link, $html_element));
  }

  /**
   * Click on the element with the provided xpath query.
   *
   * @When /^I click on the element with xpath "([^"]*)"$/
   */
  public function iClickOnTheElementWithxPath($xpath) {
    $session = $this->getSession();
    $element = $session->getPage()->find(
      'xpath',
      $session->getSelectorsHandler()->selectorToXpath('xpath', $xpath)
    );
    if (NULL === $element) {
      throw new \InvalidArgumentException(sprintf('Could not evaluate XPath: "%s"', $xpath));
    }
    $element->click();
  }

  /**
   * Fills in content's title field with a specified value.
   *
   * @When I fill in the content's title with :arg1
   */
  public function iFillInTheContentsTitleWith($arg1) {
    $page = $this->getSession()->getPage();

    $content_field_id = 'edit-title';
    $element = $page->find('css', '#edit-title');
    if (empty($element)) {
      $content_field_id = 'edit-title-field-en-0-value';
    }
    $this->fillField($content_field_id, $arg1);
  }

  /**
   * Checks that HTML response contains the specified meta tag.
   *
   * It checks the name and the content attributes values.
   *
   * @Then the response should contain the meta tag with the :arg1 name and the :arg2 content
   */
  public function responseShouldContainMetaTagWithNameAndContent($arg1, $arg2) {
    $metatag = $this->getMetaTagByName($arg1);

    assert($arg2, equals($metatag->getAttribute('content')), sprintf('The meta tag "%s" does not have "%s" as content attribute.', $arg1, $arg2));
  }

  /**
   * Gets the meta tag NodeElement from the name attribute value.
   *
   * @param string $name
   *   The name value for the meta tag.
   *
   * @return \Behat\Mink\ElementNodeElement
   *   The meta tag node element.
   */
  protected function getMetaTagByName($name) {
    $page = $this->getSession()->getPage();
    $element = $page->find('css', sprintf('meta[name="%s"]', $name));

    assert($element, isNotEmpty(), sprintf('The meta tag "%s" has not been found', $name));

    return $element;
  }

}
