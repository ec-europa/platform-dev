<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Tests\TokenHandlerTest.
 */

namespace Drupal\nexteuropa_token\Tests;

/**
 * Class TokenHandlerTest.
 *
 * @package Drupal\nexteuropa_token\Tests
 */
class TokenHandlerTest extends TokenHandlerAbstractTest {

  /**
   * Test faulty service container call.
   *
   * @expectedException \Exception
   */
  public function testFaultyServiceContainerCall() {
    nexteuropa_token_get_handler('foo');

    $reflection = new \ReflectionClass('\stdClass');
    if (!$reflection->implementsInterface('\Drupal\nexteuropa_token\TokenHandlerInterface')) {
      throw new \Exception(t('Token handler class !class must implement \Drupal\nexteuropa_token\TokenHandlerInterface interface.', array('!class' => $handlers[$name])));
    }
  }

  /**
   * Test successful service container call.
   */
  public function testSuccessfulServiceContainerCall() {
    $handler = nexteuropa_token_get_handler('hash_handler');

    $reflection = new \ReflectionClass($handler);
    $this->assertTrue($reflection->implementsInterface('Drupal\nexteuropa_token\TokenHandlerInterface'));
    $this->assertEquals($reflection->getName(), 'Drupal\nexteuropa_token\HashTokenHandler');
  }

}
