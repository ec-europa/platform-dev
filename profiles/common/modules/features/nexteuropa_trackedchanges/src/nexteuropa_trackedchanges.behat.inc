<?php

/**
 * @file
 * Contains \NextEuropaTrackedChangesSubContext.
 */

use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Behat step definitions for the NextEuropa Tracked Changes module.
 */
class NextEuropaTrackedChangesSubContext extends RawDrupalContext implements DrupalSubContextInterface {


  /**
   * {@inheritdoc}
   */
  protected $drupal;

  /**
   * Constructs a NextEuropaTrackedChangesSubContext object.
   *
   * @param \Drupal\DrupalDriverManager $drupal
   *   The Drupal driver manager.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Activates the tracking change buttons in a WYSIWYG profile.
   *
   * @param string $profile_machine_name
   *   The name or the machine name of the WYSIWYG profile.
   *
   * @Given the tracking change is activate for :arg1 WYSIWYG profile
   */
  public function theTrackingChangeIsActivateForWysiwygProfile($profile_machine_name) {
    $filters = filter_formats();
    foreach ($filters as $machine_name => $filter) {
      if ($filter->name == $profile_machine_name) {
        $profile_machine_name = $machine_name;
        break;
      }
    }

    nexteuropa_trackedchanges_enable_buttons($profile_machine_name);
  }

}
