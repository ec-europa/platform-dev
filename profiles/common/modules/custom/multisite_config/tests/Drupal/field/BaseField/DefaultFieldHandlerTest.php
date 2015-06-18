<?php

/**
 * @file
 * Contains \Tests\Drupal\field\BaseField\DefaultFieldHandler.
 */

namespace Drupal\multisite_config\Tests\Drupal\field\BaseField;

use Drupal\multisite_config\Tests\ConfigAbstractTest;
use Drupal\field\BaseField\DefaultFieldHandler;

/**
 * Class DefaultFieldHandlerTest.
 *
 * @package Drupal\multisite_config\Tests\Drupal\field\BaseField
 */
class DefaultFieldHandlerTest extends ConfigAbstractTest {

  /**
   * Test base field handler constructor.
   *
   * @dataProvider additionProvider
   */
  public function testHandlerConstructor($field_name, $type) {
    $handler = new DefaultFieldHandler($field_name, $type);

    $this->assertArrayHasKey('field_name', $handler->getField());
    $this->assertArrayHasKey('type', $handler->getField());
  }

  /**
   * Test base field saving.
   *
   * @dataProvider additionProvider
   */
  public function testFieldSaving($field_name, $type) {
    $handler = new DefaultFieldHandler($field_name, $type);

    $field = $handler->save();
    $this->assertEquals($type, $field['type']);
    $this->assertEquals($field_name, $field['field_name']);

    field_delete_field($field_name);
  }

  /**
   * Data provider.
   *
   * @see self::testHandlerConstructor()
   */
  public function additionProvider() {
    return array(
      array('field_name_' . rand(), 'text'),
    );
  }

}
