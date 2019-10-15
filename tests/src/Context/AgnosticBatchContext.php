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
  use \Drupal\nexteuropa\Context\ContextUtil;

  /**
   * Wait for the Batch API to finish.
   *
   * Wait until the id="updateprogress" element is gone,
   * or timeout after 10 minutes (600,000 ms).
   *
   * @Given /^I wait for the end of the batch job$/
   */
  public function iWaitForEndBatchJob() {
    $this->spin(function ($context) {
      $inprogress = $this->getSession()->getPage()->findById('updateprogress');
      if ($inprogress === NULL) {
        return TRUE;
      }
    }, array(), '60');
  }

}
