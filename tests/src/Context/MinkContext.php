<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MinkContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\Gherkin\Node\TableNode;
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

}
