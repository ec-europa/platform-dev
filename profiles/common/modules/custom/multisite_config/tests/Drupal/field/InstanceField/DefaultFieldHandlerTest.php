<?php

namespace Drupal\multisite_config\Tests\Drupal\field\InstanceField;

use Drupal\multisite_config\Tests\ConfigAbstractTest;
use Drupal\field\InstanceField\DefaultFieldHandler as DefaultInstanceFieldHandler;
use Drupal\field\BaseField\DefaultFieldHandler as DefaultBaseFieldHandler;

/**
 * Class DefaultFieldHandlerTest.
 *
 * @package Drupal\multisite_config\Tests\Drupal\field\InstanceField
 */
class DefaultFieldHandlerTest extends ConfigAbstractTest {

  /**
   * Test base field handler constructor.
   *
   * @dataProvider fieldDataProvider
   */
  public function testHandlerConstructor($field_name, $type, $label, $widget, $default_formatter, $teaser_formatter) {
    $base_handler = new DefaultBaseFieldHandler($field_name, $type);
    $base_handler->save();

    $handler = new DefaultInstanceFieldHandler($field_name, 'node', self::CONTENT_TYPE_WITHOUT_FIELDS);
    $instance = $handler->getField();

    $this->assertEquals(self::CONTENT_TYPE_WITHOUT_FIELDS, $instance['bundle']);
    $this->assertEquals('node', $instance['entity_type']);
    $this->assertEquals($field_name, $instance['field_name']);
    $this->assertEquals(FALSE, $instance['required']);

    field_delete_field($field_name);
  }

  /**
   * Test instance field array construction.
   *
   * @dataProvider fieldDataProvider
   */
  public function testFieldArrayConstruction($field_name, $type, $label, $widget, $default_formatter, $teaser_formatter) {
    $handler = new DefaultInstanceFieldHandler($field_name, 'node', self::CONTENT_TYPE_WITHOUT_FIELDS);

    $handler->label($label)
      ->widget($widget)
      ->display('default', $default_formatter, 'inline')
      ->display('teaser', $teaser_formatter);

    $instance = $handler->getField();

    $this->assertEquals($label, $instance['label']);
    $this->assertEquals($widget, $instance['widget']['type']);
    $this->assertEquals($default_formatter, $instance['display']['default']['type']);
    $this->assertEquals($teaser_formatter, $instance['display']['teaser']['type']);
  }

  /**
   * Test instance field creation.
   *
   * @dataProvider fieldDataProvider
   */
  public function testFieldInstanceCreation($field_name, $type, $label, $widget, $default_formatter, $teaser_formatter) {
    $base_handler = new DefaultBaseFieldHandler($field_name, $type);
    $base_handler->save();

    $handler = new DefaultInstanceFieldHandler($field_name, 'node', self::CONTENT_TYPE_WITHOUT_FIELDS);
    $handler->label($label)
      ->widget($widget)
      ->display('default', $default_formatter, 'inline')
      ->display('teaser', $teaser_formatter);

    $handler->save();

    $saved_instance = field_info_instance('node', $field_name, self::CONTENT_TYPE_WITHOUT_FIELDS);
    $this->assertEquals($label, $saved_instance['label']);
    $this->assertEquals($widget, $saved_instance['widget']['type']);
    $this->assertEquals($default_formatter, $saved_instance['display']['default']['type']);
    $this->assertEquals($teaser_formatter, $saved_instance['display']['teaser']['type']);

    field_delete_field($field_name);
  }

  /**
   * Data provider: name, type, label, widget, default and teaser formatters.
   *
   * @see self::testHandlerConstructor()
   */
  public function fieldDataProvider() {
    return array(
      array(
        'field_name_' . rand(),
        'taxonomy_term_reference',
        'Tags', 'taxonomy_autocomplete',
        'taxonomy_term_reference_link',
        'hidden',
      ),
      array(
        'field_name_' . rand(),
        'text',
        'Text',
        'text_textfield',
        'text_default',
        'text_trimmed',
      ),
    );
  }

}
