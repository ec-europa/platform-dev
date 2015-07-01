<?php

/**
 * @file
 * Contains \Drupal\multisite_config\Tests\Drupal\field_group.
 */

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
   * Test building of definition array.
   */
  public function testDefinitionArray() {

    $service = new Config();
    $field_group = $service->createFieldGroup('Test group', 'group_test_group', 'node', 'test_with_fields')
      ->setChild('title')
      ->setChild('body')
      ->setType('tab');

    $definition = $field_group->getDefinition();
    $this->assertEquals('group_test_group', $definition->group_name);
    $this->assertEquals('node', $definition->entity_type);
    $this->assertEquals('Test group', $definition->label);
    $this->assertEquals('test_with_fields', $definition->bundle);
    $this->assertEquals('tab', $definition->format_type);

    $this->assertTrue(in_array('title', $definition->children));
    $this->assertTrue(in_array('body', $definition->children));
  }

}
