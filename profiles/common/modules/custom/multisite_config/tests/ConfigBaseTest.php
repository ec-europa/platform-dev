<?php

/**
 * @file
 * Class \Drupal\multisite_config\Tests\NextEuropaDataExportAbstractTest.
 */

namespace Drupal\multisite_config\Tests;

/**
 * Class ConfigAbstractTest.
 *
 * @package Drupal\multisite_config\Tests
 */
class ConfigBaseTest extends ConfigAbstractTest {

  /**
   * Test Multisite Service container.
   */
  public function testServiceContainer() {

    $paths = glob(drupal_get_path('module', 'multisite_config') . '/lib/Drupal/*', GLOB_ONLYDIR);
    foreach ($paths as $path) {
      $name = drupal_basename($path);
      $this->assertTrue(class_exists("Drupal\\$name\\Config"));
    }

    foreach (array('user', 'system', 'taxonomy') as $name) {
      $service = multisite_config_service($name);
      $this->assertEquals("Drupal\\$name\\Config", get_class($service));
    }
  }

  /**
   * Test case when both service class and module do not exist.
   *
   * @expectedException \Exception
   *
   * @expectedExceptionMessage Service class "\Drupal\not_existing_module\Config" and module "not_existing_module" does not exists.
   */
  public function testNotExistingServiceClassAndModule() {
    $service = multisite_config_service('not_existing_module');
    $this->assertEquals('Drupal\multisite_config\ConfigBase', get_class($service));
  }

}
