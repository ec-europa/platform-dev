<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\AgnosticBatchContext.
 */

namespace Drupal\nexteuropa\Context;

use Behat\MinkExtension\Context\RawMinkContext;

/**
 * Class AgnosticBatchContext.
 *
 * It replaces Drupal\DrupalExtension\Context\BatchContext because it uses
 * JQuery library that could some tines not be loaded yet when a step is
 * executed.
 *
 * @package Drupal\nexteuropa\Context
 */
class AgnosticBatchContext extends RawMinkContext {

  /**
   * Wait for the Batch API to finish.
   *
   * Wait until the id="updateprogress" element is gone,
   * or timeout after 10 minutes (600,000 ms).
   *
   * @Given /^I wait for the end of the batch job$/
   */
  public function iWaitForEndBatchJob() {
    $this->getSession()->wait(600000, 'document.getElementById("updateprogress") == null');
  }

}
