<?php

namespace Drush\updater\Unit;

use PHPUnit\Framework\TestCase;
use Drush\updater\Controller;

/**
 * Updater test class.
 */
class UpdaterTest extends TestCase {

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    $this->drupal_major_version = getenv('DRUPAL_MAJOR_VERSION');
    $this->updaters_path = dirname(__FILE__) . '/updaters/' . $this->drupal_major_version . '/';
  }

  /**
   * Test getUpdaters().
   */
  public function testGetUpdaters() {
    $updaters = Controller::getUpdaters($this->updaters_path);
    $this->assertInternalType('array', $updaters);
    $this->assertContains($this->updaters_path . 'updater-01-maintenance.php', $updaters);
    $this->assertContains($this->updaters_path . 'updater-02-maintenance.php', $updaters);
    $this->assertContains($this->updaters_path . 'updater-03-false.php', $updaters);
  }

  /**
   * Test isValidUpdater().
   */
  public function testIsValidUpdater() {
    $updater = $this->updaters_path . 'updater-01-maintenance.php';
    $this->assertTrue(Controller::isValidUpdater($updater));
    $updater = $this->updaters_path . 'updater-02-maintenance.php';
    $this->assertTrue(Controller::isValidUpdater($updater));
    $updater = $this->updaters_path . 'updater-03-false.php';
    $this->assertTrue(Controller::isValidUpdater($updater));
    $this->assertFalse(Controller::isValidUpdater('/bin/rm'));
  }

}
