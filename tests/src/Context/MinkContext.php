<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MinkContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\Element;
use Behat\Mink\Exception\ElementNotFoundException;
use Behat\Mink\Exception\ExpectationException;
use Behat\Mink\Selector\Xpath\Escaper;
use Drupal\DrupalExtension\Context\MinkContext as DrupalExtensionMinkContext;
use GuzzleHttp\Client;

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
   * @When I fill :arg1 with:
   */
  public function iFillWith($arg1, PyStringNode $string) {
    $field = $this->getSession()->getPage()->findField($arg1);

    $field->setValue($string->getRaw());
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

}
