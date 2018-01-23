<?php

namespace Drupal\nexteuropa_token\Tests;

use Drupal\nexteuropa_token\HashTokenHandler;

/**
 * Class HashTokenHandlerTest.
 *
 * @package Drupal\nexteuropa_token\Tests
 */
class HashTokenHandlerTest extends TokenHandlerAbstractTest {

  /**
   * Instance of HashTokenHandler.
   *
   * @var \Drupal\nexteuropa_token\HashTokenHandler
   */
  protected $handler;

  static public $generatedHashes = array();

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    $this->handler = new HashTokenHandler();
    module_enable(array('nexteuropa_token_test'));
  }

  /**
   * HashTokenHandler::hookTokenInfoAlter() produces well-formed array.
   *
   * @param string $entity_type
   *   Entity type machine name.
   *
   * @dataProvider entityTypeMachineNamesProvider
   */
  public function testHookTokenInfoAlter($entity_type) {
    $data = array();
    $this->handler->hookTokenInfoAlter($data);

    $this->assertArrayHasKey('tokens', $data);
    $this->assertArrayHasKey($entity_type, $data['tokens']);
    $this->assertArrayHasKey(HashTokenHandler::TOKEN_NAME, $data['tokens'][$entity_type]);
    $this->assertArrayHasKey('name', $data['tokens'][$entity_type][HashTokenHandler::TOKEN_NAME]);
    $this->assertArrayHasKey('description', $data['tokens'][$entity_type][HashTokenHandler::TOKEN_NAME]);
  }

  /**
   * Test that nexteuropa_token_token_info_alter() actually works.
   *
   * @param string $entity_type
   *   Entity type machine name.
   *
   * @dataProvider entityTypeMachineNamesProvider
   */
  public function testAvailableTokens($entity_type) {
    $tokens = token_get_info();
    $this->assertArrayHasKey($entity_type, $tokens['tokens']);
    $this->assertArrayHasKey(HashTokenHandler::TOKEN_NAME, $tokens['tokens'][$entity_type]);
  }

  /**
   * Test HashTokenHandler::hookTokens().
   */
  public function testNodeHookTokens() {

    $type = 'node';
    $node = $this->getTestNode();
    $tokens = array(HashTokenHandler::TOKEN_NAME => HashTokenHandler::TOKEN_NAME);
    $data = array($type => $node);

    $replacements = $this->handler->hookTokens($type, $tokens, $data);
    $this->assertArrayHasKey(HashTokenHandler::TOKEN_NAME, $replacements);

    $expected_hash = $this->handler->generate(variable_get('nexteuropa_token_hash_prefix', 'prefix'), $type, $node->nid);
    $this->assertEquals($expected_hash, $replacements[HashTokenHandler::TOKEN_NAME]);
  }

  /**
   * Test hook_nexteuropa_token_token_handlers() implementation.
   */
  public function testHookHandler() {
    $handlers = module_invoke_all('nexteuropa_token_token_handlers');
    $this->assertArrayHasKey('hash_handler', $handlers);
  }

  /**
   * Test hash generation.
   *
   * @param string $prefix_one
   *   Test data from data provider.
   * @param string $entity_type_one
   *   Test data from data provider.
   * @param int $entity_id_one
   *   Test data from data provider.
   * @param string $prefix_two
   *   Test data from data provider.
   * @param string $entity_type_two
   *   Test data from data provider.
   * @param int $entity_id_two
   *   Test data from data provider.
   *
   * @dataProvider hashGenerationProvider
   */
  public function testHashGeneration($prefix_one, $entity_type_one, $entity_id_one, $prefix_two, $entity_type_two, $entity_id_two) {
    $message = sprintf('Input: %s %s %s %s %s %s', $prefix_one, $entity_type_one, $entity_id_one, $prefix_two, $entity_type_two, $entity_id_two);

    // The same input should produce always the same output.
    $first_try = $this->handler->generate($prefix_one, $entity_type_one, $entity_id_one);
    $second_try = $this->handler->generate($prefix_one, $entity_type_one, $entity_id_one);
    $this->assertEquals($first_try, $second_try, $message);

    // Two different inputs should never produce same result.
    $hash_one = $this->handler->generate($prefix_one, $entity_type_one, $entity_id_one);
    $hash_two = $this->handler->generate($prefix_two, $entity_type_two, $entity_id_two);
    $this->assertNotEquals($hash_one, $hash_two, $message);

    $message_hash = sprintf('Hashes %s %s', $hash_one, $hash_two);
    $this->assertFalse(in_array($hash_one, self::$generatedHashes), $message_hash . ' ' . $message);
    $this->assertFalse(in_array($hash_two, self::$generatedHashes), $message_hash . ' ' . $message);

    self::$generatedHashes[] = $hash_two;
    self::$generatedHashes[] = $hash_one;
  }

  /**
   * Test hook_nexteuropa_token_token_handlers_alter().
   */
  public function testHookTokenHandlersAlter() {
    $handlers = nexteuropa_token_get_token_handlers();
    $this->assertArrayHasKey('nexteuropa_token_test', $handlers);
    $this->assertEquals($handlers['nexteuropa_token_test'], '\Drupal\nexteuropa_token_test\TestTokenHandler');
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

  /**
   * Data provider: provides input for generation function.
   *
   * @return array
   *   Return PHPUnit data.
   */
  public static function hashGenerationProvider() {
    $values = array(
      array('apple', 'node', 13, 'pear', 'node', 13),
      array('apple', 'term', 23, 'apple', 'node', 23),
      array('apple', 'term', 11, 'pear', 'node', 10),
      array('apple', 'term', 112, 'pear', 'node', 105),
      array('prefix_one', 'node', 13, 'prefix_two', 'node', 12),
      array('apple', 'node', 139358673425, 'pear', 'node', 139358673425),
    );
    return $values;
  }

}
