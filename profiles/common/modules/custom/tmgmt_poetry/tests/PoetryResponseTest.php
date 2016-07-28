<?php

/**
 * @file
 * Contains Drupal\tmgmt_poetry\Tests\PoetryResponseTest.
 */

namespace Drupal\tmgmt_poetry\Tests;

use Drupal\tmgmt_poetry\Services\PoetryResponse;

/**
 * Class PoetryResponseTest.
 *
 * @package Drupal\tmgmt_poetry\Tests
 */
class PoetryResponseTest extends AbstractTest {

  /**
   * Test factory method.
   */
  public function testFactory() {
    $server = PoetryResponse::getInstance();
    $reflection = new \ReflectionClass($server);
    $this->assertEquals('Drupal\tmgmt_poetry\Services\PoetryResponse', $reflection->getName());
  }

}
