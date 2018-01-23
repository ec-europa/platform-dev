<?php

namespace Drupal\multisite_config\Tests\Drupal\field_group;

use Drupal\multisite_config\Tests\ConfigAbstractTest;
use Drupal\field_group\Config;

/**
 * Class ConfigTest.
 *
 * @package Drupal\multisite_config\Tests\Drupal\field_group
 */
class ConfigTest extends ConfigAbstractTest {

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    $this->service = new Config();
  }

  /**
   * Test building of definition array.
   */
  public function testDefinitionArray() {

    $definition = $this->getFieldGroupHandler()->getDefinition();

    $this->assertEquals('group_test_group', $definition->group_name);
    $this->assertEquals('node', $definition->entity_type);
    $this->assertEquals('Test group', $definition->label);
    $this->assertEquals(self::CONTENT_TYPE_WITH_FIELDS, $definition->bundle);
    $this->assertEquals('tab', $definition->format_type);

    $this->assertEquals('closed', $definition->format_settings['formatter']);
    $this->assertEquals('test-class-one test-class-two', $definition->format_settings['instance_settings']['classes']);
    $this->assertEquals(TRUE, $definition->format_settings['instance_settings']['required_fields']);

    $this->assertTrue(in_array('title', $definition->children));
    $this->assertTrue(in_array('body', $definition->children));
  }

  /**
   * Test building of definition array.
   */
  public function testCrud() {

    // Test creating field group definition.
    $this->getFieldGroupHandler()->save();
    $definition = $this->getFieldGroupHandler()->getDefinition();
    $group = $this->service->loadFieldGroupByIdentifier($definition->identifier);
    $this->assertEqualFieldGroupDefinition($group, $definition);

    // Test updating field group definition.
    $field_handler = $this->getFieldGroupHandler()
      ->setWeight(10)
      ->setChild('new_field')
      ->setInstanceSetting('description', 'Test description');
    $definition = $field_handler->getDefinition();
    $field_handler->save();
    $group = $this->service->loadFieldGroupByIdentifier($definition->identifier);
    $this->assertEqualFieldGroupDefinition($group, $definition);

    // Test deleting field group definition.
    $this->service->deleteFieldGroupByIdentifier($definition->identifier);
    $group = $this->service->loadFieldGroupByIdentifier($definition->identifier);
    $this->assertNull($group);
  }

  /**
   * Assert that group definitions are equal.
   *
   * @param object $group
   *   Field group definition object, loaded from the database.
   * @param object $definition
   *   Field group definition object, constructed using FieldGroupHandler.
   */
  public function assertEqualFieldGroupDefinition($group, $definition) {

    $properties = array(
      'bundle',
      'entity_type',
      'format_type',
      'group_name',
      'identifier',
      'label',
      'parent_name',
      'weight',
    );
    foreach ($properties as $property) {
      $this->assertEquals($group->{$property}, $definition->{$property});
    }

    $this->assertEquals($group->children, $definition->children, '', 0.0, 10, TRUE);
    $this->assertEquals($group->format_settings, $definition->format_settings, '', 0.0, 10, TRUE);
  }

  /**
   * Build and return test field group handler.
   *
   * @return \Drupal\field_group\FieldGroupHandler
   *   Field group handler object instance.
   */
  private function getFieldGroupHandler() {

    $field_group = $this->service->createFieldGroup('Test group', 'group_test_group', 'node', self::CONTENT_TYPE_WITH_FIELDS)
      ->setChild('title')
      ->setChild('body')
      ->setType('tab')
      ->setFormatter('closed')
      ->setInstanceSetting('classes', 'test-class-one test-class-two')
      ->setInstanceSetting('required_fields', TRUE);
    return $field_group;
  }

}
