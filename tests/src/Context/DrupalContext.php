<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\DrupalContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\TableNode;
use Drupal\DrupalExtension\Context\DrupalContext as DrupalExtensionDrupalContext;

/**
 * Provides step definitions for interacting with Drupal.
 */
class DrupalContext extends DrupalExtensionDrupalContext {

  /**
   * {@inheritdoc}
   */
  public function loggedIn() {
    $session = $this->getSession();
    $session->visit($this->locatePath('/'));

    // Check if the 'logged-in' class is present on the page.
    $element = $session->getPage();
    return $element->find('css', 'body.logged-in');
  }

  /**
   * Attempts to check a VBO checkbox in a table row containing given text.
   *
   * @param string $text
   *    Table row text to be looking for.
   *
   * @throws \Exception
   *    Thrown if no VBO checkbox has been found.
   *
   * @Then I select the :text row
   */
  public function selectVboTableRow($text) {
    $page = $this->getSession()->getPage();
    if ($checkbox = $this->getTableRow($page, $text)->find('css', '.vbo-select')) {
      $checkbox->check();
    }
    else {
      throw new \Exception(sprintf('No View Bulk Operations checkbox found on the row containing "%s", on the page %s', $text, $this->getSession()->getCurrentUrl()));
    }
  }

  /**
   * Allow for a more compact version of "@Then I select the :text row".
   *
   * @Then I select the following rows:
   */
  public function iSelectTheFollowingRows(TableNode $table) {
    // Retrieve list of text from the test scenario and flatten it.
    $list = $table->getColumnsHash();
    array_walk($list, function (&$value) {
      $value = reset($value);
    });

    // Attempt to check VBO checkboxes containing the given text.
    foreach ($list as $text) {
      $this->selectVboTableRow($text);
    }
  }

}
