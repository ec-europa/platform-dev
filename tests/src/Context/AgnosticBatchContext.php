<?php

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
   * or timeout after 3 minutes (180,000 ms).
   *
   * @Given /^I wait for the end of the batch job$/
   */
  public function iWaitForEndBatchJob() {
    $this->getSession()->wait(180000, 'document.getElementById("updateprogress") == null');
  }

}
