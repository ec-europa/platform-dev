<?php

/**
 * @file
 * Class \Drupal\multisite_config\Tests\NextEuropaDataExportAbstractTest.
 */

namespace Drupal\multisite_config\Tests;

/**
 * Class MultisiteConfigAbstractTest.
 *
 * @package Drupal\multisite_config\Tests
 */
abstract class MultisiteConfigAbstractTest extends \PHPUnit_Framework_TestCase {

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    if (!module_exists('multisite_config')) {
      throw new \Exception('multisite_config module must be enabled.');
    }
  }

}
