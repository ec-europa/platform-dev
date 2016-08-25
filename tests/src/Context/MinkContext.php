<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MinkContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Exception\ElementNotFoundException;
use Behat\Mink\Exception\ExpectationException;
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
    $fieldset = $this->getSession()->getPage()->find(
      'named',
      array('fieldset', $fieldset_locator)
    );

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

}
