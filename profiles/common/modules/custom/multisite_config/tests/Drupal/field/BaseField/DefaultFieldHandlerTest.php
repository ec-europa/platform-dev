<?php

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
   * @dataProvider fieldDataProvider
   */
  public function testHandlerConstructor($field_name, $type) {
    $handler = new DefaultFieldHandler($field_name, $type);

    $this->assertArrayHasKey('field_name', $handler->getField());
    $this->assertArrayHasKey('type', $handler->getField());
  }

  /**
   * Test base field saving.
   *
   * @dataProvider fieldDataProvider
   */
  public function testFieldSaving($field_name, $type, $module) {
    $handler = new DefaultFieldHandler($field_name, $type);

    $field = $handler->save();
    $this->assertEquals($type, $field['type']);
    $this->assertEquals($field_name, $field['field_name']);
    $this->assertEquals($module, $field['module']);
    $this->assertEquals(FALSE, $field['locked']);
    $this->assertEquals(1, $field['active']);
    $this->assertEquals(0, $field['deleted']);
    $this->assertEquals(1, $field['cardinality']);
    $this->assertEquals(FALSE, $field['translatable']);

    field_delete_field($field_name);
  }

  /**
   * Data provider: file name, field type and module providing it.
   *
   * @see self::testHandlerConstructor()
   */
  public function fieldDataProvider() {
    return array(
      array('field_name_' . rand(), 'text', 'text'),
      array('field_name_' . rand(), 'text_long', 'text'),
      array('field_name_' . rand(), 'taxonomy_term_reference', 'taxonomy'),
      array('field_name_' . rand(), 'image', 'image'),
      array('field_name_' . rand(), 'list_text', 'list'),
    );
  }

}
