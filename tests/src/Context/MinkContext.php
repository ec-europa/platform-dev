<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MinkContext.
 */

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
    $legend_element = $this->getSession()->getPage()->find('xpath', '//legend[contains(normalize-space(string(.)), ' . $legend . ')]');

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
          $item->getTagName() === 'input' &&
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
   * @param NodeElement[] $elements
   *   Array of elements to search through.
   *
   * @return NodeElement|NULL
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
   * Attempts to find and check a checkbox in a table row containing given text.
   *
   * @param string $row_text
   *    Text on the table row.
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *    Throw exception if class table row was not found.
   *
   * @Given I check the box on the :row_text row
   */
  public function checkCheckboxOnTableRow($row_text) {
    $page = $this->getSession()->getPage();
    if ($checkbox = $this->getTableRow($page, $row_text)->find('css', 'input[type=checkbox]')) {
      $checkbox->check();
      return;
    }
    throw new ExpectationException(sprintf('Found a row containing "%s", but no "%s" link on the page %s', $row_text, $checkbox, $this->getSession()->getCurrentUrl()), $this->getSession());
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
   * @param Element $element
   *    Mink element object.
   * @param string $search
   *    Table row text.
   *
   * @throws \Exception
   *    Throw exception if class table row was not found.
   *
   * @return NodeElement
   *    Table row node element.
   */
  public function getTableRow(Element $element, $search) {
    $rows = $element->findAll('css', 'tr');
    if (empty($rows)) {
      throw new \Exception(sprintf('No rows found on the page %s', $this->getSession()->getCurrentUrl()));
    }
    /** @var NodeElement $row */
    foreach ($rows as $row) {
      if (strpos($row->getText(), $search) !== FALSE) {
        return $row;
      }
    }
    throw new \Exception(sprintf('Failed to find a row containing "%s" on the page %s', $search, $this->getSession()->getCurrentUrl()));
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
    $attribs = $rules = $table->getHash();

    // Checking if attributes of the element are equal.
    foreach ($attribs as $attrib) {
      $attrib_value = $element_node->getAttribute($attrib['Attribute']);

      if ($attrib_value != $attrib['Value']) {
        throw new \Exception(sprintf('The value "%1$s" for the "%2$s" attribute on the current page is different from the expected "%3$s"', $attrib['Value'], $attrib['Attribute'], $attrib_value));
      }
    }
  }

}
