<?php

/**
 * @file
 * Contains Drupal\tmgmt_poetry\Tests\PoetryServerTest.
 */

namespace Drupal\tmgmt_poetry\Tests;

use Drupal\tmgmt_poetry\Services\PoetryServer;

/**
 * Class PoetryServerTest.
 *
 * @package Drupal\tmgmt_poetry\Tests
 */
class PoetryServerTest extends AbstractTest {

  /**
   * Smoke test.
   */
  public function testSmokeTest() {
    $server = PoetryServer::getInstance();
    $this->assertTrue(TRUE);
  }

}
