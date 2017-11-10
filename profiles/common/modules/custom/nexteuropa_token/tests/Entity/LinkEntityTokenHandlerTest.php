<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Tests\LinkEntityTokenHandlerTest.
 */

namespace Drupal\nexteuropa_token\Tests\Entity;

use Drupal\nexteuropa_token\Entity\LinkTokenHandler;
use Drupal\nexteuropa_token\Tests\TokenHandlerAbstractTest;

/**
 * Class LinkEntityTokenHandlerTest.
 *
 * @package Drupal\nexteuropa_token\Tests\Entity
 */
class LinkEntityTokenHandlerTest extends TokenHandlerAbstractTest {

  /**
   * Instance of HashTokenHandler.
   *
   * @var \Drupal\nexteuropa_token\Entity\LinkTokenHandler
   */
  protected $handler;

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    $this->handler = new LinkTokenHandler();
  }

  /**
   * HashTokenHandler::hookTokenInfoAlter() produces well-formed array.
   *
   * @dataProvider entityTypeMachineNamesProvider
   */
  public function testHookTokenInfoAlter($entity_type) {
    $data = array();
    $this->handler->hookTokenInfoAlter($data);

    $this->assertArrayHasKey('tokens', $data);
    $this->assertArrayHasKey($entity_type, $data['tokens']);

    $token_name = $this->handler->getTokenName();
    $this->assertArrayHasKey($token_name, $data['tokens'][$entity_type]);
    $this->assertArrayHasKey('name', $data['tokens'][$entity_type][$token_name]);
    $this->assertArrayHasKey('description', $data['tokens'][$entity_type][$token_name]);
  }

  /**
   * Test hook_nexteuropa_token_token_handlers() implementation.
   */
  public function testHookHandler() {
    $handlers = module_invoke_all('nexteuropa_token_token_handlers');
    $this->assertArrayHasKey('link_entity_handler', $handlers);
  }

  /**
   * Test we get entity view modes correctly.
   *
   * @dataProvider tokenOriginalValues
   */
  public function testParseToken($original, $entity_id) {

    $this->assertEquals($entity_id, $this->handler->getEntityIdFromToken($original));
  }

  /**
   * Data provider: provides list of token $original values.
   *
   * @return array
   *   Return PHPUnit data.
   */
  public static function tokenOriginalValues() {
    return array(
      // Valid tokens.
      array('[node:1:link]', 1),
      array('[user:12:link]', 12),
      array('[term:123:link]', 123),
      // Not valid tokens.
      array('[comment:123:link]', ''),
      array('[any-text:123:link]', ''),
      array('[not:valid:link]', ''),
      array('[node:123:linkit]', ''),
    );
  }

  /**
   * Data provider: provides list of entity machine names.
   *
   * @return array
   *   Return PHPUnit data.
   */
  public static function entityTypeMachineNamesProvider() {
    return array(array('node'), array('user'), array('term'));
  }

}
