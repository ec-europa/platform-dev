<?php

namespace Drupal\nexteuropa_token\Tests\Entity;

use Drupal\nexteuropa_token\Entity\UrlTokenHandler;
use Drupal\nexteuropa_token\Tests\TokenHandlerAbstractTest;

/**
 * Class UrlEntityTokenHandlerTest.
 *
 * @package Drupal\nexteuropa_token\Tests\Entity
 */
class UrlEntityTokenHandlerTest extends TokenHandlerAbstractTest {

  /**
   * Instance of HashTokenHandler.
   *
   * @var \Drupal\nexteuropa_token\Entity\UrlTokenHandler
   */
  protected $handler;

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    $this->handler = new UrlTokenHandler();
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
    $this->assertArrayHasKey('url_entity_handler', $handlers);
  }

  /**
   * Test we get entity view modes correctly.
   *
   * @param string $original
   *    Token in original format.
   * @param int $entity_id
   *    Entity ID.
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
   *    Return PHPUnit data.
   */
  public static function tokenOriginalValues() {
    return array(
      // Valid tokens.
      array('[node:1:url]', 1),
      array('[user:12:url]', 12),
      array('[term:123:url]', 123),
      // Not valid tokens.
      array('[comment:123:url]', ''),
      array('[any-text:123:url]', ''),
      array('[not:valid:token]', ''),
      array('[node:123:uri]', ''),
      array('[node:123:uriiii]', ''),
    );
  }


  /**
   * Data provider: provides list of entity machine names.
   *
   * @return array
   *    Return PHPUnit data.
   */
  public static function entityTypeMachineNamesProvider() {
    return array(array('node'), array('user'), array('term'));
  }

}
