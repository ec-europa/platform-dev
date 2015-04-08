<?php

/**
 * @file
 * Contains \Drupal\nexteuropa_token\Tests\HashTokenHandlerTest
 */

namespace Drupal\nexteuropa_token\Tests;

use Drupal\nexteuropa_token\HashTokenHandler;

class HashTokenHandlerTest extends TokenHandlerAbstractTest {

  /**
   * Instance of HashTokenHandler.
   *
   * @var \Drupal\nexteuropa_token\HashTokenHandler
   */
  protected $handler;

  static $generated_hashes = array();

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    $this->handler = new HashTokenHandler();
  }

  /**
   * Test that HashTokenHandler::hookTokenInfoAlter() produces well-formed array.
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
   * @dataProvider entityTypeMachineNamesProvider
   */
  public function testAvailableTokens($entity_type) {
    $tokens = token_get_info();
    $this->assertArrayHasKey($entity_type, $tokens['tokens']);
    $this->assertArrayHasKey(HashTokenHandler::TOKEN_NAME, $tokens['tokens'][$entity_type]);
  }

  /**
   * Test HashTokenHandler::hookTokens()
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
    $this->assertFalse(in_array($hash_one, self::$generated_hashes), $message_hash . ' '. $message);
    $this->assertFalse(in_array($hash_two, self::$generated_hashes), $message_hash . ' '. $message);

    self::$generated_hashes[] = $hash_two;
    self::$generated_hashes[] = $hash_one;
  }

  /**
   * Data provider: provides list of entity machine names.
   *
   * @return array
   */
  public static function entityTypeMachineNamesProvider() {
    return array(array('node'), array('user'), array('term'));
  }

  /**
   * Data provider: provides input for generation function.
   *
   * @return array
   */
  public static function hashGenerationProvider() {
    $values = array(
      array('apple', 'node', 13, 'pear', 'node', 13),
      array('apple', 'term', 23, 'apple', 'node', 23),
      array('apple', 'term', 11, 'pear', 'node', 10),
      array('apple', 'term', 112, 'pear', 'node', 105),
      array('prefix_one', 'node', 13, 'prefix_two', 'node', 12),
      array('apple', 'node', 139358673425, 'pear', 'node', 139358673425),
//      array('very-very-very-very-very-very-very-very-very-very-long', 'node', 13, 'very-very-very-very-long', 'node', 12),
    );

//    $values = array();
//    for ($i = 0; $i < 10000; $i++) {
//      $values[] = array(md5(rand()), md5(rand()), rand(0, 100000), md5(rand()), md5(rand()), rand(0, 100000));
//    }
    return $values;
  }
}
