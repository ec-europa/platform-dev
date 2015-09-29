<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Context\MinkContext.
 */

namespace Drupal\nexteuropa\Context;

use Drupal\DrupalExtension\Context\MinkContext as DrupalExtensionMinkContext;

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

}
