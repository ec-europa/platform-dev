<?php

/**
 * @file
 * Class \Drupal\nexteuropa_data_export\Tests\NextEuropaDataExportAbstractTest.
 */

namespace Drupal\nexteuropa_data_export\Tests;

use Behat\Mink\Mink;
use Behat\Mink\Session;
use Behat\Mink\Driver\GoutteDriver;
use Behat\Mink\Driver\Goutte\Client as GoutteClient;
use Drupal\Driver\DrupalDriver;

/**
 * Class NextEuropaDataExportAbstractTest.
 *
 * @package Drupal\nexteuropa_data_export\Tests
 */
abstract class NextEuropaDataExportAbstractTest extends \PHPUnit_Framework_TestCase {

  /**
   * Mink instance.
   *
   * @var \Behat\Mink\Mink
   */
  protected $mink = NULL;

  /**
   * Drupal driver instance.
   *
   * @var \Drupal\Driver\DrupalDriver
   */
  protected $driver = NULL;

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    if (!module_exists('nexteuropa_data_export_test')) {
      throw new \Exception('nexteuropa_data_export_test module must be enabled.');
    }

    // Setup Mink.
    $this->mink = new Mink(array('goutte' => new Session(new GoutteDriver(new GoutteClient()))));
    $this->mink->setDefaultSessionName('goutte');

    // Setup Drupal driver.
    $this->driver = new DrupalDriver(DRUPAL_ROOT, BASE_URL);
    $this->driver->setCoreFromVersion();
  }

  /**
   * Mink wrapper: get current session.
   *
   * @return \Behat\Mink\Session
   *    Session object instance.
   */
  public function getSession() {
    return $this->mink->getSession();
  }

  /**
   * Mink wrapper: visit specified relative path.
   *
   * @param string $path
   *    Relative URL path.
   */
  public function visit($path) {
    $this->getSession()->visit(BASE_URL . '/' . $path);
  }

  /**
   * Mink wrapper: get current page.
   *
   * @return \Behat\Mink\Element\DocumentElement
   *    Document object instance.
   */
  public function page() {
    return $this->getSession()->getPage();
  }

}
